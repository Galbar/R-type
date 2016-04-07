#ifndef POWER_UP_HPP
#define POWER_UP_HPP
#include "Hum2D/Hum2D.hpp"
#include "MOGL/MOGL.hpp"
#include "GamePlugin.hpp"
#include "ActorFactory.hpp"
#include "Collider.hpp"

class PowerUpBuilder : public ActorConstructor
{
    void construct(h2d::Actor&, const tiled::Object&) override;
};

class PowerUp : public h2d::Behavior
{
public:
    PowerUp(mogl::AnimatedSprite* sprite, Collider* collider, h2d::Kinematic* kinematic);
    void init() override;
    void fixedUpdate() override;
    void onDestroy() override;

    void onEnable();
    void onDisable();

private:
    mogl::MultimediaOGL* p_mogl;
    mogl::AnimatedSprite* p_sprite;
    Collider* p_collider;
    h2d::Kinematic* p_kinematic;
    GamePlugin* p_game_pl;
};

#endif /* ifndef POWER_UP_HPP */
