#include "Owl.hpp"
#include "Collider.hpp"
#include "Bullet.hpp"

void OwlBuilder::construct(h2d::Actor& actor, const tiled::Object& tmx_object)
{
    auto collider = actor.addBehavior<Collider>(1, 1, Collider::Type::Enemy);
    auto kinematic = actor.addBehavior<h2d::Kinematic>();
    auto shooter = tmx_object.getProperties().get("shooter");
    if (shooter.getType() != tiled::Value::Type::BOOL)
    {
        shooter = tiled::Value(false);
    }
    actor.addBehavior<Owl>(collider, kinematic, shooter.getBool());
}

Owl::Owl(Collider* collider, h2d::Kinematic* kinematic, bool shooter):
p_collider(collider),
p_kinematic(kinematic),
p_shooter(shooter)
{}

void Owl::init()
{
    p_mogl = actor().game().getPlugin<mogl::MultimediaOGL>();
    p_game_pl = actor().game().getPlugin<GamePlugin>();
    p_sprite = actor().addBehavior<mogl::AnimatedSprite>(1, 1, p_mogl->spriteAnimations().get("owl-to-left"));

    p_clk.reset();
}

void Owl::fixedUpdate()
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


    p_kinematic->velocity().x = p_game_pl->getCameraSpeed() - 5;
    p_kinematic->velocity().y = 0.0;

    if (p_clk.getTime().asSeconds() > 0.25 && p_shooter)
    {
        shoot();
        p_clk.reset();
    }
}

void Owl::shoot()
{
    auto bullet = actor().game().makeActor();
    auto collider = bullet->addBehavior<Collider>(1, 1, Collider::Type::EnemyBullet);
    auto kinematic = bullet->addBehavior<h2d::Kinematic>();
    auto sprite = bullet->addBehavior<mogl::AnimatedSprite>(1, 1, p_mogl->spriteAnimations().get("butterfly-shoot"));
    bullet->addBehavior<Bullet>(collider, kinematic, 0, 3);
    bullet->transform().x = actor().transform().x;
    bullet->transform().y = actor().transform().y + 1;
    actor().game().getPlugin<GamePlugin>()->addActor(bullet);
}
