#ifndef GAME_PLUGIN_HPP
#define GAME_PLUGIN_HPP
#include "Hum2D/Hum2D.hpp"
#include "MOGL/MOGL.hpp"
#include "tiled/tiled.hpp"
#include <unordered_set>
#include <vector>
#include "Collider.hpp"
#include "ActorFactory.hpp"

class GamePlugin : public h2d::Plugin
{
public:
    GamePlugin();
    virtual ~GamePlugin();

    void gameStart() override;
    void gameEnd() override;
    void preFixedUpdate() override;
    void postFixedUpdate() override;
    void postUpdate() override;

    void setCameraSpeed(float speed);
    float getCameraSpeed() const;
    void setActorFactory(ActorFactory& factory);

    void addActor(h2d::Actor*);
    void addCollider(Collider*);
    void removeCollider(Collider*);

private:
    void updateActiveActors();

    h2d::Kinematic* p_camera_kinematic;
    mogl::MultimediaOGL* p_mogl;
    ActorFactory* p_factory;
    float p_camera_speed;
    std::unordered_set<h2d::Actor*> p_inactive_actors;
    std::unordered_set<Collider*> p_player_collider;
    std::unordered_set<Collider*> p_enemy_collider;
    std::unordered_set<Collider*> p_player_bullet_collider;
    std::unordered_set<Collider*> p_enemy_bullet_collider;
    std::unordered_set<Collider*> p_wall_collider;
};
#endif /* ifndef GAME_PLUGIN_HPP */
