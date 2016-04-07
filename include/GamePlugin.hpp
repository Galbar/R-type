#ifndef GAME_PLUGIN_HPP
#define GAME_PLUGIN_HPP
#include "Hum2D/Hum2D.hpp"
#include "MOGL/MOGL.hpp"
#include "tiled/tiled.hpp"
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
    void removeActor(h2d::Actor* actor);
    void addCollider(Collider*);
    void removeCollider(Collider*);


    const tiled::Map& getMap() const;
    void changeLevel(const std::string& name);

private:
    void updateActiveActors();

    struct Scene
    {
        std::vector<std::string> textures;
        std::vector<std::string> animations;
        std::vector<h2d::Actor*> actors;
    };

    Scene* p_scene;
    h2d::Kinematic* p_camera_kinematic;
    mogl::MultimediaOGL* p_mogl;
    ActorFactory* p_factory;
    bool p_change_level;
    std::string p_next_level_name;
    float p_camera_speed;
    tiled::Map p_active_map;
    std::unordered_set<h2d::Actor*>* p_actors;
    std::unordered_set<Collider*>* p_colliders;
};
#endif /* ifndef GAME_PLUGIN_HPP */
