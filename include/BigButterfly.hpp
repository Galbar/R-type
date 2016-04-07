#ifndef BIG_BUTTERFLY_HPP
#define BIG_BUTTERFLY_HPP
#include "Hum2D/Hum2D.hpp"
#include "MOGL/MOGL.hpp"
#include "GamePlugin.hpp"
#include "ActorFactory.hpp"
#include "Collider.hpp"

class BigButterflyBuilder : public ActorConstructor
{
    void construct(h2d::Actor&, const tiled::Object&) override;
};

class BigButterfly : public h2d::Behavior
{
public:
    BigButterfly(Collider* collider, h2d::Kinematic* kinematic);
    void init() override;
    void fixedUpdate() override;

private:
    mogl::MultimediaOGL* p_mogl;
    Collider* p_collider;
    h2d::Kinematic* p_kinematic;
    GamePlugin* p_game_pl;

    void shoot(float x, float y);

    float p_angle, p_angle_stepsize;
    h2d::Clock p_clk;
};

#endif /* ifndef BIG_BUTTERFLY_HPP */


