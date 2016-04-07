#ifndef BULLET_HPP
#define BULLET_HPP
#include "Hum2D/Hum2D.hpp"
#include "MOGL/MOGL.hpp"
#include "GamePlugin.hpp"
#include "ActorFactory.hpp"
#include "Collider.hpp"

class Bullet : public h2d::Behavior
{
public:
    Bullet(Collider* collider, h2d::Kinematic* kinematic, float vel_x, float vel_y);
    void init() override;
    void fixedUpdate() override;
    void onDestroy() override;

private:
    Collider* p_collider;
    h2d::Kinematic* p_kinematic;
    GamePlugin* p_game_pl;

    float p_vel_x, p_vel_y;
};

#endif /* ifndef BULLET_HPP */
