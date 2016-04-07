#ifndef BEE_HPP
#define BEE_HPP
#include "Hum2D/Hum2D.hpp"
#include "MOGL/MOGL.hpp"
#include "GamePlugin.hpp"
#include "ActorFactory.hpp"
#include "Collider.hpp"

class BeeBuilder : public ActorConstructor
{
    void construct(h2d::Actor&, const tiled::Object&);
};

class Bee : public h2d::Behavior
{
public:
    Bee(Collider* collider, h2d::Kinematic* kinematic, const std::string&);
    void init() override;
    void fixedUpdate() override;

private:
    mogl::MultimediaOGL* p_mogl;
    mogl::AnimatedSprite* p_sprite;
    Collider* p_collider;
    h2d::Kinematic* p_kinematic;
    GamePlugin* p_game_pl;
    std::string p_next_level;

    void shoot(float x, float y);

    bool p_dead, p_go_up;
    float p_vel;
    h2d::Clock p_clk;
};

#endif /* ifndef BEE_HPP */
