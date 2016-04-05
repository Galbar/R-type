#include "Bird.hpp"
#include "Collider.hpp"
#include "Bullet.hpp"
#include "Defines.hpp"

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
    double pos_y = actor().transform().y;
    double width = p_mogl->getCamera().getPosition().x + ORTHO_WIDTH;
    double height = p_mogl->getCamera().getPosition().y;
    if (pos_x > width - ORTHO_WIDTH/6)
    {
        p_kinematic->velocity().x -= 5;
    }
    else if (pos_x > width - 2*ORTHO_WIDTH/6  && p_num_bullets == 3)
    {
        shoot();
        p_shooting = true;
        p_clk.reset();
    }
    else if (p_num_bullets > 0 && p_clk.getTime().asSeconds() > 0.5)
    {
        shoot();
        p_clk.reset();
        if (p_num_bullets == 0)
        {
            p_circle = true;
        }
    }
    else if (p_circle)
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
    else
    {
        p_kinematic->velocity().x -= 5;
    }
}

void Bird::shoot()
{
    auto bullet = actor().game().makeActor();
    bullet->transform().x = actor().transform().x + 10;
    bullet->transform().y = actor().transform().y;
    bullet->addBehavior<Bullet>();
    actor().game().getPlugin<GamePlugin>()->addActor(bullet);
    --p_num_bullets;
}
