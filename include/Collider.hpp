#ifndef COLLIDER_HPP
#define COLLIDER_HPP
#include <SFML/Graphics.hpp>
#include <queue>
#include "Hum2D/Hum2D.hpp"

class Collider;
struct Collision
{
    Collider* other;
    sf::FloatRect intersection;
};

class Collider : public h2d::Behavior
{
public:
    enum class Type { Player, PowerUpGun, PowerUpShield, Enemy, PlayerBullet, EnemyBullet, Wall };
    Collider(float width, float height, Type type);
    Collider(const sf::FloatRect& rect, Type type);

    void init() override;
    void onActivate() override;
    void onDeactivate() override;
    void onDestroy() override;

    void setRect(const sf::FloatRect& rect);
    sf::FloatRect getRect() const;

    Type getType() const;
    void setType(Type type);

    void pushCollision(const Collision& collision);
    bool getNextCollision(Collision& collision);
    void clearCollisions();

private:
    Type p_type;
    sf::FloatRect p_rect;
    std::queue<Collision> p_collisions;
};

#endif /* ifndef COLLIDER_HPP */
