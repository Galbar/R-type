#ifndef BIRD_HPP
#define BIRD_HPP
#include "Hum2D/Hum2D.hpp"
#include "MOGL/MOGL.hpp"
#include "GamePlugin.hpp"
#include "ActorFactory.hpp"
#include "Collider.hpp"

class BirdBuilder : public ActorConstructor
{
    void construct(h2d::Actor&, const tiled::Object&) override;
};

class Bird : public h2d::Behavior
{
public:
    Bird(mogl::AnimatedSprite* sprite, Collider* collider, h2d::Kinematic* kinematic);
    void init() override;
    void fixedUpdate() override;

private:
    mogl::MultimediaOGL* p_mogl;
    mogl::AnimatedSprite* p_sprite;
    Collider* p_collider;
    h2d::Kinematic* p_kinematic;
    GamePlugin* p_game_pl;

    void shoot();

    bool p_circle;
    int p_num_bullets;
    float p_angle, p_angle_stepsize, p_angle_limit;
    h2d::Clock p_clk;
};

#endif /* ifndef BIRD_HPP */
