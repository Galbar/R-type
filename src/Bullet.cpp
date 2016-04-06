#include "Bullet.hpp"
#include "Collider.hpp"
#include "Defines.hpp"

Bullet::Bullet(mogl::AnimatedSprite* sprite, Collider* collider, h2d::Kinematic* kinematic, float vel_x, float vel_y):
p_sprite(sprite),
p_collider(collider),
p_kinematic(kinematic),
p_vel_x(vel_x),
p_vel_y(vel_y)
{}

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
    }

    p_kinematic->velocity().x = p_game_pl->getCameraSpeed() + p_vel_x;
    p_kinematic->velocity().y = p_vel_y;
}
