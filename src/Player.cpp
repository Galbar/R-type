#include "Player.hpp"
#include "Collider.hpp"
#include "Bullet.hpp"
#include "Defines.hpp"

double abs(double x)
{
    return x < 0 ? -x : x;
}

void PlayerBuilder::construct(h2d::Actor& actor, const tiled::Object& tmx_object)
{
    auto mogl = actor.game().getPlugin<mogl::MultimediaOGL>();
    auto sprite = actor.addBehavior<mogl::AnimatedSprite>(1, 1, mogl->spriteAnimations().get("butterfly-main"));
    auto collider = actor.addBehavior<Collider>(0.75, 0.5, Collider::Type::Player);
    collider->setRect(sf::FloatRect(0.25, 0, 0.5, 0.5));
    auto kinematic = actor.addBehavior<h2d::Kinematic>();
    actor.addBehavior<Player>(sprite, collider, kinematic);
}

void WallBuilder::construct(h2d::Actor& actor, const tiled::Object& tmx_object)
{
    actor.addBehavior<Collider>(tmx_object.getWidth() / TILE_SIZE, tmx_object.getHeight() / TILE_SIZE, Collider::Type::Wall);
    actor.game().getPlugin<GamePlugin>()->addActor(&actor);
}


void PowerUpBuilder::construct(h2d::Actor& actor, const tiled::Object& object)
{
    auto type = object.getProperties().get("type");
    if (type.getType() == tiled::Value::Type::STRING)
    {
        auto mogl = actor.game().getPlugin<mogl::MultimediaOGL>();
        if (type.getString() == "gun")
        {
            actor.addBehavior<Collider>(1, 1, Collider::Type::PowerUpGun);
            actor.addBehavior<mogl::AnimatedSprite>(1, 1, mogl->spriteAnimations().get("butterfly-shield"));
        }
        else if (type.getString() == "shield")
        {
            actor.addBehavior<Collider>(1, 1, Collider::Type::PowerUpShield);
            actor.addBehavior<mogl::AnimatedSprite>(1, 1, mogl->spriteAnimations().get("butterfly-shield"));
        }
        else
        {
            h2d_log("PowerUp with unknown type. Ignoring...");
            actor.game().destroy(actor);
            return;
        }
        actor.game().getPlugin<GamePlugin>()->addActor(&actor);
    }
    else
    {
        h2d_log("PowerUp without type. Ignoring...");
        actor.game().destroy(actor);
    }
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
}

void Player::fixedUpdate()
{
    Collision collision;
    while (p_collider->getNextCollision(collision))
    {
        if (collision.other->getType() == Collider::Type::Wall)
        {
            if (collision.intersection.width > collision.intersection.height)
            {
                if (abs(collision.intersection.top - actor().transform().y) <= 0.001)
                {
                    actor().transform().y += collision.intersection.height;
                }
                else
                {
                    actor().transform().y -= collision.intersection.height;
                }
            }
            else
            {
                if (abs(collision.intersection.left - actor().transform().x) <= 0.001)
                {
                    actor().transform().x += collision.intersection.width;
                }
                else
                {
                    actor().transform().x -= collision.intersection.width;
                }
            }
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
                p_game_pl->changeLevel("credits");
                return;
            }
        }
        else if (collision.other->getType() == Collider::Type::PowerUpGun)
        {
            p_pwu_gun += 2;
            actor().game().destroy(collision.other->actor());
        }
        else if (collision.other->getType() == Collider::Type::PowerUpShield)
        {
            ++p_shield;
            actor().game().destroy(collision.other->actor());
        }
    }

    p_kinematic->velocity().x = p_game_pl->getCameraSpeed();
    p_kinematic->velocity().y = 0.0;

    if (p_mogl->input().isKeyDown(sf::Keyboard::Left) and actor().transform().x > p_mogl->getCamera().getPosition().x)
    {
        p_kinematic->velocity().x -= 3;
    }
    if (p_mogl->input().isKeyDown(sf::Keyboard::Right) and actor().transform().x < p_mogl->getCamera().getPosition().x + ORTHO_WIDTH - 1)
    {
        p_kinematic->velocity().x += 3;
    }
    if (p_mogl->input().isKeyDown(sf::Keyboard::Up) and actor().transform().y > p_mogl->getCamera().getPosition().y)
    {
        p_kinematic->velocity().y -= 3;
    }
    if (p_mogl->input().isKeyDown(sf::Keyboard::Down) and actor().transform().y < p_mogl->getCamera().getPosition().y + ORTHO_HEIGHT - 1)
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
}

void Player::shoot(float x, float y, float xx, float yy)
{
    auto bullet = actor().game().makeActor();
    auto collider = bullet->addBehavior<Collider>(1, 1, Collider::Type::PlayerBullet);
    auto kinematic = bullet->addBehavior<h2d::Kinematic>();
    auto sprite = bullet->addBehavior<mogl::AnimatedSprite>(1, 1, p_mogl->spriteAnimations().get("butterfly-shoot"));
    bullet->addBehavior<Bullet>(collider, kinematic, xx, yy);
    bullet->transform().x = actor().transform().x + x;
    bullet->transform().y = actor().transform().y + y;
    actor().game().getPlugin<GamePlugin>()->addActor(bullet);
}

void Player::onDestroy()
{
}
