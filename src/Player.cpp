#include "Player.hpp"
#include "Collider.hpp"
#include "Bullet.hpp"

void PlayerBuilder::construct(h2d::Actor& actor, const tiled::Object& tmx_object)
{
    auto mogl = actor.game().getPlugin<mogl::MultimediaOGL>();
    auto sprite = actor.addBehavior<mogl::AnimatedSprite>(1, 1, mogl->spriteAnimations().get("butterfly-main.anim"));
    auto collider = actor.addBehavior<Collider>(1, 1, Collider::Type::Player);
    auto kinematic = actor.addBehavior<h2d::Kinematic>();
    actor.transform().z = 10;
    actor.transform().x = 10;
    actor.transform().y = 10;
    actor.addBehavior<Player>(sprite, collider, kinematic);
}

Player::Player(mogl::AnimatedSprite* sprite, Collider* collider, h2d::Kinematic* kinematic):
p_sprite(sprite),
p_collider(collider),
p_kinematic(kinematic),
p_shield(3),
p_pwu_gun(0)
{}

void Player::init()
{
    p_mogl = actor().game().getPlugin<mogl::MultimediaOGL>();
    p_game_pl = actor().game().getPlugin<GamePlugin>();
    p_game_pl->addActor(&actor());
}

void Player::fixedUpdate()
{
    bool coll_left, coll_right, coll_top, coll_bot;
    coll_left = coll_right = coll_top = coll_bot = false;

    Collision collision;
    while (p_collider->getNextCollision(collision))
    {
        if (collision.other->getType() == Collider::Type::Wall)
        {
            coll_left = p_collider->getRect().left < (collision.intersection.left + collision.intersection.width);
            coll_right = (p_collider->getRect().left + p_collider->getRect().width) > collision.intersection.left;
            coll_top = p_collider->getRect().top < (collision.intersection.top + collision.intersection.height);
            coll_bot = (p_collider->getRect().top + p_collider->getRect().height) > collision.intersection.top;
        }
        else if (collision.other->getType() == Collider::Type::Enemy
                || collision.other->getType() == Collider::Type::EnemyBullet)
        {
            if (p_shield > 1)
            {
                --p_shield;
            }
            else if (p_pwu_gun > 0)
            {
                --p_pwu_gun;
            }
            else
            {
                actor().game().destroy(actor());
                return;
            }
        }
        else if (collision.other->getType() == Collider::Type::PowerUpGun)
        {
            p_pwu_gun += 2;
        }
        else if (collision.other->getType() == Collider::Type::PowerUpShield)
        {
            ++p_shield;
        }
    }

    p_kinematic->velocity().x = p_game_pl->getCameraSpeed();
    p_kinematic->velocity().y = 0.0;

    if (p_mogl->input().isKeyDown(sf::Keyboard::Left))
    {
        p_kinematic->velocity().x -= 3;
    }
    if (p_mogl->input().isKeyDown(sf::Keyboard::Right))
    {
        p_kinematic->velocity().x += 3;
    }
    if (p_mogl->input().isKeyDown(sf::Keyboard::Up))
    {
        p_kinematic->velocity().y -= 3;
    }
    if (p_mogl->input().isKeyDown(sf::Keyboard::Down))
    {
        p_kinematic->velocity().y += 3;
    }

    if (p_mogl->input().isKeyPressed(sf::Keyboard::Space))
    {
        shoot(1, 0, 3, 0);
        if (p_pwu_gun > 0)
        {
            shoot(1, 1, 3, 3);
            shoot(1, -1, 3, -3);
            --p_pwu_gun;
        }
        if (p_shield >= 5)
        {
            shoot(1, 1, 3, 0);
        }
        if (p_shield >= 8)
        {
            shoot(1, -1, 3, 0);
        }
    }

    if (coll_left && p_kinematic->velocity().x < 0)
    {
        p_kinematic->velocity().x = 0;
    }
    if (coll_right && p_kinematic->velocity().x > 0)
    {
        p_kinematic->velocity().x = 0;
    }
    if (coll_top && p_kinematic->velocity().y < 0)
    {
        p_kinematic->velocity().y = 0;
    }
    if (coll_bot&& p_kinematic->velocity().y > 0)
    {
        p_kinematic->velocity().y = 0;
    }
}

void Player::shoot(float x, float y, float xx, float yy)
{
    auto bullet = actor().game().makeActor();
    auto collider = bullet->addBehavior<Collider>(1, 1, Collider::Type::EnemyBullet);
    auto kinematic = bullet->addBehavior<h2d::Kinematic>();
    auto sprite = bullet->addBehavior<mogl::AnimatedSprite>(1, 1, p_mogl->spriteAnimations().get("butterfly-shoot.anim"));
    bullet->addBehavior<Bullet>(collider, kinematic, xx, yy);
    bullet->transform().x = actor().transform().x + x;
    bullet->transform().y = actor().transform().y + y;
    actor().game().getPlugin<GamePlugin>()->addActor(bullet);
}

void Player::onDestroy()
{
    h2d_log("Player muerto");
}
