#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "Hum2D/Hum2D.hpp"
#include "MOGL/MOGL.hpp"
#include "GamePlugin.hpp"
#include "ActorFactory.hpp"
#include "Collider.hpp"

class PlayerBuilder : public ActorConstructor
{
    void construct(h2d::Actor&, const tiled::Object&) override;
};

class Player : public h2d::Behavior
{
public:
    Player(mogl::AnimatedSprite* sprite, Collider* collider, h2d::Kinematic* kinematic);
    void init() override;
    void fixedUpdate() override;
    void onDestroy() override;

private:
    mogl::MultimediaOGL* p_mogl;
    mogl::AnimatedSprite* p_sprite;
    Collider* p_collider;
    h2d::Kinematic* p_kinematic;
    GamePlugin* p_game_pl;
};

#endif /* ifndef PLAYER_HPP */
