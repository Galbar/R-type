#include "Bullet.hpp"
#include "Collider.hpp"
#include "Defines.hpp"

Bullet::Bullet(Collider* collider, h2d::Kinematic* kinematic, float vel_x, float vel_y):
p_collider(collider),
p_kinematic(kinematic),
p_vel_x(vel_x),
p_vel_y(vel_y)
{}

void Bullet::init()
{
    p_game_pl = actor().game().getPlugin<GamePlugin>();
    auto mogl = actor().game().getPlugin<mogl::MultimediaOGL>();
    p_collider->setRect(sf::FloatRect(0.25, 0, 0.5, 0.5));
    mogl->sounds().play("shoot", 50, false);
}

void Bullet::fixedUpdate()
{
    Collision collision;
    while (p_collider->getNextCollision(collision))
    {
        if (collision.other->getType() == Collider::Type::Wall)
        {
            actor().game().destroy(actor());
            return;
        }
        if (p_collider->getType() == Collider::Type::PlayerBullet && collision.other->getType() == Collider::Type::Enemy)
        {
            auto mogl = actor().game().getPlugin<mogl::MultimediaOGL>();
            mogl->sounds().play("success", 50, false);
            actor().game().destroy(actor());
            return;
        }
        else if (collision.other->getType() == Collider::Type::EnemyBullet && p_collider->getType() == Collider::Type::PlayerBullet)
        {
            actor().game().destroy(actor());
            return;
        }
        else if (p_collider->getType() == Collider::Type::EnemyBullet && collision.other->getType() == Collider::Type::PlayerBullet)
        {
            actor().game().destroy(actor());
            return;
        }
    }

    p_kinematic->velocity().x = p_game_pl->getCameraSpeed() + p_vel_x;
    p_kinematic->velocity().y = p_vel_y;
}

void Bullet::onDestroy()
{
}
