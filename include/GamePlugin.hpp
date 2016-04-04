#ifndef GAME_PLUGIN_HPP
#define GAME_PLUGIN_HPP
#include "Hum2D/Hum2D.hpp"
#include "MOGL/MOGL.hpp"
#include "tiled/tiled.hpp"
#include <set>
#include <vector>
#include "Collider.hpp"

class GamePlugin : public h2d::Plugin
{
public:
    GamePlugin();
    virtual ~GamePlugin();

    void gameStart() override;
    void gameEnd() override;
    void preFixedUpdate() override;
    void postUpdate() override;

    void setCameraSpeed(float speed);
    float getCameraSpeed() const;

    void addActor(h2d::Actor*);
    void addCollider(Collider*);
    void removeCollider(Collider*);

private:
    void updateActiveActors();

    h2d::Kinematic* p_camera_kinematic;
    mogl::MultimediaOGL* p_mogl;
    float p_camera_speed;
    std::vector<h2d::Actor*> p_actors;
    std::vector<h2d::Actor*>::iterator p_actors_lower;
    std::vector<h2d::Actor*>::iterator p_actors_upper;
    std::set<Collider*> p_player_collider;
    std::set<Collider*> p_enemy_collider;
    std::set<Collider*> p_player_bullet_collider;
    std::set<Collider*> p_enemy_bullet_collider;
    std::set<Collider*> p_wall_collider;
};
#endif /* ifndef GAME_PLUGIN_HPP */
