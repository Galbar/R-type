#include "GamePlugin.hpp"

GamePlugin::GamePlugin()
{

}

GamePlugin::~GamePlugin()
{

}

void GamePlugin::gameStart()
{
    p_camera_kinematic = game().makeActor()->addBehavior<h2d::Kinematic>();
    p_mogl = game().getPlugin<mogl::MultimediaOGL>();
}

void GamePlugin::postUpdate()
{
    p_camera_kinematic->velocity().x = p_camera_speed;
    h2d::Transformation cam_transform = p_camera_kinematic->simulate(game().fixedUpdateLag());
    p_mogl->getCamera().setPosition(glm::vec3(cam_transform.x, cam_transform.y, -1));
    p_mogl->getCamera().setCenter(glm::vec3(cam_transform.x, cam_transform.y, 1));
}

void GamePlugin::setCameraSpeed(float speed)
{
    p_camera_speed = speed;
}

float GamePlugin::getCameraSpeed() const
{
    return p_camera_speed;
}
