#ifndef GAME_BEHAVIOR_HPP
#define GAME_BEHAVIOR_HPP
#include "Hum2D/Hum2D.hpp"
#include "MOGL/MOGL.hpp"

class GamePlugin;
class GameBehavior : public h2d::Behavior
{
public:
    virtual void init() override;
    virtual void fixedUpdate() override;

private:
    static GamePlugin* s_p_game_pl;
    static mogl::MultimediaOGL* s_p_mogl;
};

#endif /* ifndef GAME_BEHAVIOR_HPP */
