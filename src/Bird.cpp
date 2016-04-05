#include "Bird.hpp"
#include "Collider.hpp"

void BirdBuilder::construct(h2d::Actor& actor, const tiled::Object& tmx_object)
{
    auto mogl = actor.game().getPlugin<mogl::MultimediaOGL>();
    auto sprite = actor.addBehavior<mogl::AnimatedSprite>(1, 1, mogl->spriteAnimations().get("bird_anim"));
    auto collider = actor.addBehavior<Collider>(1, 1, Collider::Type::Enemy);
    auto kinematic = actor.addBehavior<h2d::Kinematic>();
    actor.transform().z = 10;
    actor.transform().x = 10;
    actor.transform().y = 10;
    actor.addBehavior<Bird>(sprite, collider, kinematic);
}

Bird::Bird(mogl::AnimatedSprite* sprite, Collider* collider, h2d::Kinematic* kinematic):
p_sprite(sprite),
p_collider(collider),
p_kinematic(kinematic),
p_shooting(false),
p_circle(false),
p_num_bullets(3),
p_angle(0.0)
{}

void Bird::init()
{
    p_mogl = actor().game().getPlugin<mogl::MultimediaOGL>();
    p_game_pl = actor().game().getPlugin<GamePlugin>();
}

void Bird::fixedUpdate()
{
    Collision collision;
    while (p_collider->getNextCollision(collision) && !p_sprite->isEnabled())
    {
        if (collision.other->getType() == Collider::Type::PlayerBullet)
        {
            /*
            p_sprite->enable();
            p_collider->onDeactivate();
            p_kinematic->velocity().x = 0;
            p_kinematic->velocity().y = 0;
            */
            actor().game().destroy(actor());
        }
    }

    if (!p_sprite->isEnabled())
    {
        p_kinematic->velocity().x = p_game_pl->getCameraSpeed();
        p_kinematic->velocity().y = 0.0;

        if (p_shooting && p_clk.reset().asSeconds() > 0.5)
        {
            auto bullet = actor().game().makeActor();
            bullet->addBehavior<Bullet>();
            --p_num_bullets;
            if (p_num_bullets == 0)
            {
                p_shooting = false;
                p_num_bullets = 3;
                p_circle = true;
            }
        }

        if (p_circle)
        {
            float angle_stepsize = 0.1;

            p_kinematic->velocity().x *= cos(p_angle);
            p_kinematic->velocity().y *= sin(p_angle);

            p_angle += angle_stepsize;

            if (p_angle < (3*3.14)/4)
            {
                p_circle = false;
            }
        }

        double pos = actor().transform().x;
        if (pos < 0.0)//limite
        {
            /*
            p_sprite->enable();
            p_collider->onDeactivate();
            p_kinematic->velocity().x = 0;
            p_kinematic->velocity().y = 0;
            */
            actor().game().destroy(actor());
        }
        else if (pos > 10.0)//limite
        {
            p_kinematic->velocity().x -= 5;
        }
        else if (pos == 9.0 && !p_shooting)
        {
            auto bullet = actor().game().makeActor();
            bullet->addBehavior<Bullet>();
            --p_num_bullets;
            p_shooting = true;
            p_clk.reset();
        }
        else if (actor().transform().y < 5.0)
        {
            p_kinematic->velocity().x -= 5;
        }
    }
}

void Bird::onDestroy()
{}
