#ifndef PLAY_BUTTON_HPP
#define PLAY_BUTTON_HPP
#include "Hum2D/Hum2D.hpp"
#include "MOGL/MOGL.hpp"
#include "Defines.hpp"
#include <SFML/Graphics.hpp>
#include "ActorFactory.hpp"
#include "GamePlugin.hpp"

class PlayButtonBuilder : public ActorConstructor
{
    void construct(h2d::Actor&, const tiled::Object&) override;
};

class PlayButton : public h2d::Behavior
{
public:
    PlayButton(float width, float height);
    void fixedUpdate() override;
private:
    float p_width, p_height;
};
#endif /* ifndef PLAY_BUTTON_HPP */
