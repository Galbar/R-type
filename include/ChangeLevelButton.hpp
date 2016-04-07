#ifndef PLAY_BUTTON_HPP
#define PLAY_BUTTON_HPP
#include "Hum2D/Hum2D.hpp"
#include "MOGL/MOGL.hpp"
#include "Defines.hpp"
#include <SFML/Graphics.hpp>
#include "ActorFactory.hpp"
#include "GamePlugin.hpp"

class ChangeLevelButtonBuilder: public ActorConstructor
{
    void construct(h2d::Actor&, const tiled::Object&) override;
};

class ChangeLevelButton : public h2d::Behavior
{
public:
    ChangeLevelButton(float width, float height, const std::string& target);
    void fixedUpdate() override;
private:
    float p_width, p_height;
    std::string p_target;
};
#endif /* ifndef PLAY_BUTTON_HPP */
