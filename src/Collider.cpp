#include "Collider.hpp"
#include "GamePlugin.hpp"

Collider::Collider(float width, float height, Type type):
Collider(sf::FloatRect(0, 0, width, height), type)
{}

Collider::Collider(const sf::FloatRect& rect, Type type):
p_type(type),
p_rect(rect)
{}

void Collider::init()
{
    onActivate();
}

void Collider::onActivate()
{
    actor().game().getPlugin<GamePlugin>()->addCollider(this);
}

void Collider::onDeactivate()
{
    actor().game().getPlugin<GamePlugin>()->removeCollider(this);
}

void Collider::onDestroy()
{
    onDeactivate();
}

void Collider::setRect(const sf::FloatRect& rect)
{
    p_rect = rect;
}

sf::FloatRect Collider::getRect() const
{
    sf::FloatRect ret_val (
            actor().transform().x + p_rect.left,
            actor().transform().y + p_rect.top,
            actor().transform().scale_x * p_rect.width,
            actor().transform().scale_y * p_rect.height
            );
    return ret_val;
}

Collider::Type Collider::getType() const
{
    return p_type;
}

void Collider::setType(Type type)
{
    onDeactivate();
    p_type = type;
    onActivate();
}

void Collider::pushCollision(const Collision& collision)
{
    p_collisions.push(collision);
}

bool Collider::getNextCollision(Collision& collision)
{
    if (!p_collisions.empty())
    {
        collision = p_collisions.front();
        p_collisions.pop();
        return true;
    }
    return false;
}

void Collider::clearCollisions()
{
    while (!p_collisions.empty())
    {
        p_collisions.pop();
    }
}
