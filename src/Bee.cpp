#include "Bee.hpp"
#include "Collider.hpp"
#include "Bullet.hpp"
#include "Defines.hpp"

void BeeBuilder::construct(h2d::Actor& actor, const tiled::Object& tmx_object)
{
    auto collider = actor.addBehavior<Collider>(1, 1, Collider::Type::Enemy);
    auto kinematic = actor.addBehavior<h2d::Kinematic>();
    actor.transform().x = 20;
    actor.transform().y = 10;
    actor.addBehavior<Bee>(collider, kinematic);
}

Bee::Bee(Collider* collider, h2d::Kinematic* kinematic):
p_collider(collider),
p_kinematic(kinematic),
p_dead(false),
p_go_up(true),
p_vel(3)
{}

void Bee::init()
{
    p_mogl = actor().game().getPlugin<mogl::MultimediaOGL>();
    p_game_pl = actor().game().getPlugin<GamePlugin>();
    p_sprite = actor().addBehavior<mogl::AnimatedSprite>(1, 1, p_mogl->spriteAnimations().get("bee-left"));

    p_clk.reset();
}

void Bee::fixedUpdate()
{
    Collision collision;
    while (p_collider->getNextCollision(collision))
    {
        if (collision.other->getType() == Collider::Type::PlayerBullet)
        {
            p_dead = true;
        }
    }

    if (!p_dead)
    {
        //Como es un boss, la camara en principio esta quieta, pero por si acaso
        p_kinematic->velocity().x = p_game_pl->getCameraSpeed();

        if (p_go_up)
        {
            p_kinematic->velocity().y = -4;
            p_go_up = actor().transform().y > p_mogl->getCamera().getPosition().y + 1.5;
        }
        else
        {
            p_kinematic->velocity().y = 4;
            p_go_up = actor().transform().y > p_mogl->getCamera().getPosition().y + ORTHO_HEIGHT - 3;
        }

        if (p_clk.getTime().asSeconds() > 0.5)
        {
            shoot(-1, 0);
            shoot(-1, 1);
            shoot(-1, -1);
            p_clk.reset();
        }
    }
    else
    {
        p_kinematic->velocity().x = p_game_pl->getCameraSpeed() - 8;
        p_kinematic->velocity().y = 0.0;
    }
}

void Bee::shoot(float x, float y)
{
    auto bullet = actor().game().makeActor();
    auto collider = bullet->addBehavior<Collider>(1, 1, Collider::Type::EnemyBullet);
    auto kinematic = bullet->addBehavior<h2d::Kinematic>();
    auto sprite = bullet->addBehavior<mogl::AnimatedSprite>(1, 1, p_mogl->spriteAnimations().get("butterfly-shoot"));
    bullet->addBehavior<Bullet>(collider, kinematic, 3*x, 3*y);
    bullet->transform().x = actor().transform().x + x;
    bullet->transform().y = actor().transform().y + y;
    actor().game().getPlugin<GamePlugin>()->addActor(bullet);
}
