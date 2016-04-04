#include "Player.hpp"
#include "Collider.hpp"

void PlayerBuilder::construct(h2d::Actor& actor, const tiled::Object& tmx_object)
{
    auto mogl = actor.game().getPlugin<mogl::MultimediaOGL>();
    auto sprite = actor.addBehavior<mogl::AnimatedSprite>(1, 1, mogl->spriteAnimations().get("player_anim"));
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
p_kinematic(kinematic)
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
            h2d_log("wall!!!");
        }
    }
    h2d_log("collisions done!!!");

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
}

void Player::onDestroy()
{
    h2d_log("Player muerto");
}
