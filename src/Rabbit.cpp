#include "Rabbit.hpp"
#include "Collider.hpp"
#include "Bullet.hpp"
#include "Defines.hpp"

void RabbitBuilder::construct(h2d::Actor& actor, const tiled::Object& tmx_object)
{
    auto collider = actor.addBehavior<Collider>(1, 1, Collider::Type::Enemy);
    auto kinematic = actor.addBehavior<h2d::Kinematic>();
    bool shooter = tmx_object.getProperties().get("shooter").getBool();
    actor.transform().z = 10;
    actor.transform().x = 23;
    actor.transform().y = 10;
    actor.addBehavior<Rabbit>(collider, kinematic, shooter);
}

Rabbit::Rabbit(Collider* collider, h2d::Kinematic* kinematic, bool shooter):
p_collider(collider),
p_kinematic(kinematic),
p_shooter(shooter),
p_jump(false),
p_stop(true),
p_vel(-2)
{}

void Rabbit::init()
{
    p_mogl = actor().game().getPlugin<mogl::MultimediaOGL>();
    p_game_pl = actor().game().getPlugin<GamePlugin>();
    p_sprite = actor().addBehavior<mogl::AnimatedSprite>(1, 1, p_mogl->spriteAnimations().get("rabbit-left-stop"));

    p_floor = actor().transform().y;
    p_clk.reset();
}

void Rabbit::fixedUpdate()
{
    Collision collision;
    while (p_collider->getNextCollision(collision))
    {
        if (collision.other->getType() == Collider::Type::PlayerBullet)
        {
            actor().game().destroy(actor());
            return;
        }
        else if (collision.other->getType() == Collider::Type::Wall)
        {
            if (p_collider->getRect().left <= (collision.intersection.left + collision.intersection.width)
                || (p_collider->getRect().left + p_collider->getRect().width) >= collision.intersection.left)
            {
                p_vel *= -1;
            }
        }
    }


    p_kinematic->velocity().x = p_game_pl->getCameraSpeed() + p_vel;
    p_kinematic->velocity().y = 0.0;

    double time = p_clk.getTime().asSeconds();
    if (time > 0.75)
    {
        if (p_shooter)
        {
            shoot();
        }
        p_clk.reset();
    }

    if (p_stop && time < 0.75)
    {
        if (p_vel < 0)
        {
            p_sprite = actor().addBehavior<mogl::AnimatedSprite>(1, 1, p_mogl->spriteAnimations().get("rabbit-left-stop"));
        }
        else
        {
            p_sprite = actor().addBehavior<mogl::AnimatedSprite>(1, 1, p_mogl->spriteAnimations().get("rabbit-right-stop"));
        }
        p_jump = true;
        p_kinematic->velocity().x = p_game_pl->getCameraSpeed();
    }
    else if (actor().transform().y > p_floor - 3 && p_jump)
    {
        if (p_vel < 0)
        {
            p_sprite = actor().addBehavior<mogl::AnimatedSprite>(1, 1, p_mogl->spriteAnimations().get("rabbit-left-up"));
        }
        else
        {
            p_sprite = actor().addBehavior<mogl::AnimatedSprite>(1, 1, p_mogl->spriteAnimations().get("rabbit-right-up"));
        }
        p_kinematic->velocity().y -= 5;
        p_stop = false;
    }
    else
    {
        p_kinematic->velocity().y += 5;
        p_jump = false;
        p_stop = actor().transform().y > p_floor;
    }
}

void Rabbit::shoot()
{
    auto bullet = actor().game().makeActor();
    auto collider = bullet->addBehavior<Collider>(1, 1, Collider::Type::EnemyBullet);
    auto kinematic = bullet->addBehavior<h2d::Kinematic>();
    auto sprite = bullet->addBehavior<mogl::AnimatedSprite>(1, 1, p_mogl->spriteAnimations().get("butterfly-shoot"));
    float direction = 1;
    if (p_vel < 0) direction *= -1;
    bullet->addBehavior<Bullet>(collider, kinematic, 2.5*direction, 0);
    bullet->transform().x = actor().transform().x + direction;
    bullet->transform().y = actor().transform().y;
    actor().game().getPlugin<GamePlugin>()->addActor(bullet);
}
