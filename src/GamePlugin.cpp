#include "GamePlugin.hpp"
#include "Defines.hpp"
#include <algorithm>

bool compareActors(h2d::Actor* a, h2d::Actor*b)
{
    return a->transform().x < a->transform().x;
}

GamePlugin::GamePlugin():
p_actors_lower(p_actors.begin()),
p_actors_upper(p_actors.end())
{

}

GamePlugin::~GamePlugin()
{

}

void GamePlugin::gameStart()
{
    p_camera_kinematic = game().makeActor()->addBehavior<h2d::Kinematic>();
    p_mogl = game().getPlugin<mogl::MultimediaOGL>();
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

void GamePlugin::addActor(h2d::Actor* actor)
{
    p_actors.insert(std::upper_bound(p_actors.begin(), p_actors.end(), actor, compareActors), actor);
    if ((*p_actors_lower)->transform().x <= actor->transform().x
            && (*p_actors_upper)->transform().x >= actor->transform().x)
    {
        if (!actor->isActive())
        {
            actor->activate();
        }
    }
    else
    {
        if (actor->isActive())
        {
            actor->deactivate();
        }
    }
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
    auto prev_x = p_camera_kinematic->actor().transform().x;
    float min = p_mogl->getCamera().getPosition().x - 10;
    float max = min + ORTHO_WIDTH + 10;
    p_camera_kinematic->actor().transform().x = min;
    auto new_lower = std::upper_bound(p_actors_lower, p_actors_upper, &p_camera_kinematic->actor(), compareActors);
    p_camera_kinematic->actor().transform().x = max;
    auto new_upper = std::upper_bound(p_actors_upper, p_actors.end(), &p_camera_kinematic->actor(), compareActors);
    p_camera_kinematic->actor().transform().x = prev_x;

    for (auto it = p_actors_lower; it != new_lower; ++it)
    {
        (*it)->deactivate();
    }

    for (auto it = p_actors_upper; it != new_upper; ++it)
    {
        (*it)->activate();
    }

    p_actors_lower = new_lower;
    p_actors_upper = new_upper;
}
