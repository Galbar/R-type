#include "Bird.hpp"
#include "Collider.hpp"
#include "Bullet.hpp"
#include "Defines.hpp"

void BirdBuilder::construct(h2d::Actor& actor, const tiled::Object& tmx_object)
{
    auto mogl = actor.game().getPlugin<mogl::MultimediaOGL>();
    auto sprite = actor.addBehavior<mogl::AnimatedSprite>(1, 1, mogl->spriteAnimations().get("red-bird-to-left"));
    auto collider = actor.addBehavior<Collider>(1, 1, Collider::Type::Enemy);
    auto kinematic = actor.addBehavior<h2d::Kinematic>();
    actor.transform().z = 10;
    actor.transform().x = 25;
    actor.transform().y = 10;
    actor.addBehavior<Bird>(collider, kinematic);
}

Bird::Bird(Collider* collider, h2d::Kinematic* kinematic):
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
        p_angle_stepsize = 0.05;
        p_angle_limit = 2*3.14;
    }
    else
    {
        p_angle = (3*3.14)/2;
        p_angle_stepsize = -0.05;
        p_angle_limit = 0;
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
        p_kinematic->velocity().x -= 3;
        p_clk.reset();
    }
    else if (pos_x > width - 5*ORTHO_WIDTH/6  && p_num_bullets > 0)
    {
        if (p_clk.getTime().asSeconds() > 0.25)
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
        p_kinematic->velocity().x += 7*cos(p_angle);
        p_kinematic->velocity().y += 7*sin(p_angle);

        p_angle += p_angle_stepsize;
        if (p_angle_stepsize > 0)
        {
            if (p_angle > p_angle_limit)
            {
                p_circle = false;
            }
        }
        else
        {
            if (p_angle < p_angle_limit)
            {
                p_circle = false;
            }
        }
        p_clk.reset();
    }
    else
    {
        p_kinematic->velocity().x -= 3;
        if (p_clk.getTime().asSeconds() > 3.0)
        {
            p_num_bullets = 3;
        }
        if (actor().transform().y > p_mogl->getCamera().getPosition().y/2)
        {
            p_angle = 3.14/2;
        }
        else
        {
            p_angle = (3*3.14)/2;
        }
    }
}

void Bird::shoot()
{
    auto bullet = actor().game().makeActor();
    auto collider = bullet->addBehavior<Collider>(1, 1, Collider::Type::EnemyBullet);
    auto kinematic = bullet->addBehavior<h2d::Kinematic>();
    auto sprite = bullet->addBehavior<mogl::AnimatedSprite>(1, 1, p_mogl->spriteAnimations().get("butterfly-shoot"));
    bullet->addBehavior<Bullet>(collider, kinematic, -5, 0);
    bullet->transform().x = actor().transform().x - 1;
    bullet->transform().y = actor().transform().y;
    actor().game().getPlugin<GamePlugin>()->addActor(bullet);
    --p_num_bullets;
}
