#ifndef RABBIT_HPP
#define RABBIT_HPP
#include "Hum2D/Hum2D.hpp"
#include "MOGL/MOGL.hpp"
#include "GamePlugin.hpp"
#include "ActorFactory.hpp"
#include "Collider.hpp"

class RabbitBuilder : public ActorConstructor
{
    void construct(h2d::Actor&, const tiled::Object&);
};

class Rabbit : public h2d::Behavior
{
public:
    Rabbit(Collider* collider, h2d::Kinematic* kinematic, bool shooter);
    void init() override;
    void fixedUpdate() override;

private:
    mogl::MultimediaOGL* p_mogl;
    mogl::Sprite* p_sprite;
    Collider* p_collider;
    h2d::Kinematic* p_kinematic;
    GamePlugin* p_game_pl;

    void shoot();

    bool p_shooter, p_jump, p_stop;
    float p_floor, p_vel;
    h2d::Clock p_clk;
};

#endif /* ifndef RABBIT_HPP */
