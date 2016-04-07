#include "BigButterfly.hpp"
#include "Collider.hpp"
#include "Bullet.hpp"

void BigButterflyBuilder::construct(h2d::Actor& actor, const tiled::Object& tmx_object)
{
    auto mogl = actor.game().getPlugin<mogl::MultimediaOGL>();
    auto sprite = actor.addBehavior<mogl::AnimatedSprite>(1, 1, mogl->spriteAnimations().get("big-butterfly-left"));
    auto collider = actor.addBehavior<Collider>(1, 1, Collider::Type::Enemy);
    auto kinematic = actor.addBehavior<h2d::Kinematic>();
    actor.transform().z = 10;
    actor.transform().x = 25;
    actor.transform().y = 10;
    actor.addBehavior<BigButterfly>(collider, kinematic);
}

BigButterfly::BigButterfly(Collider* collider, h2d::Kinematic* kinematic):
p_collider(collider),
p_kinematic(kinematic),
p_angle(0.0),
p_angle_stepsize(0.1)
{}

void BigButterfly::init()
{
    p_mogl = actor().game().getPlugin<mogl::MultimediaOGL>();
    p_game_pl = actor().game().getPlugin<GamePlugin>();
}

void BigButterfly::fixedUpdate()
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


    p_kinematic->velocity().x = p_game_pl->getCameraSpeed() + 6*cos(p_angle);
    p_kinematic->velocity().y = 6*sin(p_angle);

    p_angle += p_angle_stepsize;

    if (p_clk.getTime().asSeconds() > 0.75)
    {
        shoot(-1,0);
        shoot(-1,0.5);
        shoot(-1,1);
        shoot(-1,-0.5);
        shoot(-1,-1);
        shoot(-1,1.5);
        shoot(-1,-1.5);
        p_clk.reset();
    }
}

void BigButterfly::shoot(float x, float y)
{
    auto bullet = actor().game().makeActor();
    auto collider = bullet->addBehavior<Collider>(1, 1, Collider::Type::EnemyBullet);
    auto kinematic = bullet->addBehavior<h2d::Kinematic>();
    auto sprite = bullet->addBehavior<mogl::AnimatedSprite>(1, 1, p_mogl->spriteAnimations().get("butterfly-shoot"));
    bullet->addBehavior<Bullet>(collider, kinematic, -5, 0);
    bullet->transform().x = actor().transform().x + x;
    bullet->transform().y = actor().transform().y + y;
    actor().game().getPlugin<GamePlugin>()->addActor(bullet);
}
