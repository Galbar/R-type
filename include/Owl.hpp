#ifndef OWL_HPP
#define OWL_HPP
#include "Hum2D/Hum2D.hpp"
#include "MOGL/MOGL.hpp"
#include "GamePlugin.hpp"
#include "ActorFactory.hpp"
#include "Collider.hpp"

class OwlBuilder : public ActorConstructor
{
    void construct(h2d::Actor&, const tiled::Object&);
};

class Owl : public h2d::Behavior
{
public:
    Owl(Collider* collider, h2d::Kinematic* kinematic, bool shooter);
    void init() override;
    void fixedUpdate() override;

private:
    mogl::MultimediaOGL* p_mogl;
    mogl::AnimatedSprite* p_sprite;
    Collider* p_collider;
    h2d::Kinematic* p_kinematic;
    GamePlugin* p_game_pl;

    void shoot();

    bool p_shooter;
    h2d::Clock p_clk;
};

#endif /* ifndef OWL_HPP */
