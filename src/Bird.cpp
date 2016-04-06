#include "Bird.hpp"
#include "Collider.hpp"
#include "Bullet.hpp"
#include "Defines.hpp"

void BirdBuilder::construct(h2d::Actor& actor, const tiled::Object& tmx_object)
{
    auto mogl = actor.game().getPlugin<mogl::MultimediaOGL>();
    //auto sprite = actor.addBehavior<mogl::AnimatedSprite>(1, 1, mogl->spriteAnimations().get("bird_anim"));
    auto collider = actor.addBehavior<Collider>(1, 1, Collider::Type::Enemy);
    auto kinematic = actor.addBehavior<h2d::Kinematic>();
    actor.transform().z = 10;
    actor.transform().x = 10;
    actor.transform().y = 10;
    actor.addBehavior<Bird>(nullptr, collider, kinematic);
}

Bird::Bird(mogl::AnimatedSprite* sprite, Collider* collider, h2d::Kinematic* kinematic):
p_sprite(sprite),
p_collider(collider),
p_kinematic(kinematic),
p_circle(false),
p_num_bullets(3)
{}

void Bird::init()
{
    p_mogl = actor().game().getPlugin<mogl::MultimediaOGL>();
    p_game_pl = actor().game().getPlugin<GamePlugin>();

    if (actor().transform().y > p_mogl->getCamera().getPosition().y/2)
    {
        p_angle = 3.14/2;
        p_angle_stepsize = 0.1;
        p_angle_limit = (3*3.14)/2;
    }
    else
    {
        p_angle = (3*3.14)/2;
        p_angle_stepsize = -0.1;
        p_angle_limit = 3.14/2;
    }
}

void Bird::fixedUpdate()
{
    Collision collision;
    while (p_collider->getNextCollision(collision))
    {
        if (collision.other->getType() == Collider::Type::PlayerBullet)
        {
            actor().game().destroy(actor());
            return;
        }
    }


    p_kinematic->velocity().x = p_game_pl->getCameraSpeed();
    p_kinematic->velocity().y = 0.0;

    double pos_x = actor().transform().x;
    double width = p_mogl->getCamera().getPosition().x + ORTHO_WIDTH;
    if (pos_x > width - ORTHO_WIDTH/6)
    {
        p_kinematic->velocity().x -= 5;
        p_clk.reset();
    }
    else if (pos_x > width - 2*ORTHO_WIDTH/6  && p_num_bullets > 0)
    {
        if (p_clk.getTime().asSeconds() > 0.5)
        {
            shoot();
            p_clk.reset();
            if (p_num_bullets == 0)
            {
                p_circle = true;
            }
        }
    }
    else if (p_circle)
    {
        p_kinematic->velocity().x += 10*cos(p_angle);
        p_kinematic->velocity().y += 10*sin(p_angle);

        if (p_angle_stepsize > 0)
        {
            p_angle += p_angle_stepsize;
            if (p_angle > p_angle_limit)
            {
                p_circle = false;
            }
        }
        else
        {
            p_angle -= p_angle_stepsize;
            if (p_angle < p_angle_limit)
            {
                p_circle = false;
            }
        }
    }
    else
    {
        p_kinematic->velocity().x -= 5;
    }
}

void Bird::shoot()
{
    auto bullet = actor().game().makeActor();
    bullet->addBehavior<Bullet>(p_sprite, p_collider, p_kinematic, 3, 0);
    bullet->transform().x = actor().transform().x + 10;
    bullet->transform().y = actor().transform().y;
    actor().game().getPlugin<GamePlugin>()->addActor(bullet);
    --p_num_bullets;
}
