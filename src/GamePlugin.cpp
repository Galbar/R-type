#include "GamePlugin.hpp"
#include "Defines.hpp"
#include <algorithm>
#include "GameBehavior.hpp"
#include "Resources.hpp"

bool compareActors(h2d::Actor* a, h2d::Actor*b)
{
    return a->transform().x < b->transform().x;
}

GamePlugin::GamePlugin()
{

}

GamePlugin::~GamePlugin()
{

}

void GamePlugin::gameStart()
{
    p_camera_kinematic = game().makeActor()->addBehavior<h2d::Kinematic>();
    p_mogl = game().getPlugin<mogl::MultimediaOGL>();

    // TODO: Load resources
    loadResources(*p_mogl, "./res/resources.def");

    // TODO: Read configuration
}

void GamePlugin::gameEnd()
{
}

void GamePlugin::preFixedUpdate()
{
    sf::FloatRect intersection;
    for (Collider* player_col : p_player_collider)
    {
        player_col->clearCollisions();
        for (Collider* enemy_col : p_enemy_collider)
        {
            enemy_col->clearCollisions();
            if (player_col->getRect().intersects(enemy_col->getRect(), intersection))
            {
                Collision col { enemy_col, intersection };
                player_col->pushCollision(col);
                col.other = player_col;
                enemy_col->pushCollision(col);
            }
        }

        for (Collider* enemy_bullet_col : p_enemy_bullet_collider)
        {
            enemy_bullet_col->clearCollisions();
            if (player_col->getRect().intersects(enemy_bullet_col->getRect(), intersection))
            {
                Collision col { enemy_bullet_col, intersection };
                player_col->pushCollision(col);
                col.other = player_col;
                enemy_bullet_col->pushCollision(col);
            }
        }

        for (Collider* wall : p_wall_collider)
        {
            wall->clearCollisions();
            if (player_col->getRect().intersects(wall->getRect(), intersection))
            {
                Collision col { wall, intersection };
                player_col->pushCollision(col);
                col.other = player_col;
                wall->pushCollision(col);
            }
        }
    }

    for (Collider* enemy_col : p_enemy_collider)
    {
        for (Collider* wall : p_wall_collider)
        {
            if (enemy_col->getRect().intersects(wall->getRect(), intersection))
            {
                Collision col { wall, intersection };
                enemy_col->pushCollision(col);
                col.other = enemy_col;
                wall->pushCollision(col);
            }
        }

        for (Collider* player_bullet_col : p_player_bullet_collider)
        {
            if (enemy_col->getRect().intersects(player_bullet_col->getRect(), intersection))
            {
                Collision col { player_bullet_col, intersection };
                enemy_col->pushCollision(col);
                col.other = enemy_col;
                player_bullet_col->pushCollision(col);
            }
        }
    }

    for (Collider* enemy_bullet_col : p_enemy_bullet_collider)
    {
        for (Collider* wall : p_wall_collider)
        {
            if (enemy_bullet_col->getRect().intersects(wall->getRect(), intersection))
            {
                Collision col { wall, intersection };
                enemy_bullet_col->pushCollision(col);
                col.other = enemy_bullet_col;
                wall->pushCollision(col);
            }
        }

        for (Collider* player_bullet_col : p_player_bullet_collider)
        {
            player_bullet_col->clearCollisions();
            if (enemy_bullet_col->getRect().intersects(player_bullet_col->getRect(), intersection))
            {
                Collision col { player_bullet_col, intersection };
                enemy_bullet_col->pushCollision(col);
                col.other = enemy_bullet_col;
                player_bullet_col->pushCollision(col);
            }
        }
    }
}

void GamePlugin::postFixedUpdate()
{
    // TODO: Change scene, if needed
    static bool initialized = false;
    if (!initialized)
    {
        auto a = game().makeActor();
        p_factory->build("Player", *a, tiled::Object());
        initialized = true;
    }
}

void GamePlugin::postUpdate()
{
    p_camera_kinematic->velocity().x = p_camera_speed;
    h2d::Transformation cam_transform = p_camera_kinematic->simulate(game().fixedUpdateLag());
    p_mogl->getCamera().setPosition(glm::vec3(cam_transform.x, cam_transform.y, -1));
    p_mogl->getCamera().setCenter(glm::vec3(cam_transform.x, cam_transform.y, 1));
    updateActiveActors();
}

void GamePlugin::setCameraSpeed(float speed)
{
    p_camera_speed = speed;
}

float GamePlugin::getCameraSpeed() const
{
    return p_camera_speed;
}


void GamePlugin::setActorFactory(ActorFactory& factory)
{
    p_factory = & factory;
}

void GamePlugin::addActor(h2d::Actor* actor)
{
    p_inactive_actors.insert(actor);
    actor->deactivate();
}

void GamePlugin::addCollider(Collider* collider)
{
    switch (collider->getType()) {
        case Collider::Type::PlayerBullet:
            p_player_bullet_collider.insert(collider);
            break;
        case Collider::Type::EnemyBullet:
            p_enemy_bullet_collider.insert(collider);
            break;
        case Collider::Type::Wall:
            p_wall_collider.insert(collider);
            break;
        case Collider::Type::Player:
            p_player_collider.insert(collider);
            break;
        case Collider::Type::Enemy:
            p_enemy_collider.insert(collider);
            break;
    }
}

void GamePlugin::removeCollider(Collider* collider)
{
    switch (collider->getType()) {
        case Collider::Type::PlayerBullet:
            p_player_bullet_collider.erase(collider);
            break;
        case Collider::Type::EnemyBullet:
            p_enemy_bullet_collider.erase(collider);
            break;
        case Collider::Type::Wall:
            p_wall_collider.erase(collider);
            break;
        case Collider::Type::Player:
            p_player_collider.erase(collider);
            break;
        case Collider::Type::Enemy:
            p_enemy_collider.erase(collider);
            break;
    }
}

void GamePlugin::updateActiveActors()
{
    float max = p_mogl->getCamera().getPosition().x + ORTHO_WIDTH + 3;

    std::vector<h2d::Actor*> to_remove;
    for (h2d::Actor* actor : p_inactive_actors)
    {
        if (actor->transform().x < max)
        {
            actor->addBehavior<GameBehavior>();
            actor->activate();
            to_remove.push_back(actor);
        }
    }

    for(auto a : to_remove)
    {
        p_inactive_actors.erase(a);
    }
}
