#include "Hum2D/Hum2D.hpp"
#include "MOGL/MOGL.hpp"
#include "tiled/tiled.hpp"

class GamePlugin : public h2d::Plugin
{
public:
    GamePlugin();
    virtual ~GamePlugin();

    void gameStart() override;
    void postUpdate() override;

    void setCameraSpeed(float speed);
    float getCameraSpeed() const;

private:
    h2d::Kinematic* p_camera_kinematic;
    mogl::MultimediaOGL* p_mogl;
    float p_camera_speed;
};
