#include "ChangeLevelButton.hpp"

void ChangeLevelButtonBuilder::construct(h2d::Actor& actor, const tiled::Object& object)
{
    auto value = object.getProperties().get("target");
    if (value.getType() != tiled::Value::Type::STRING)
    {
        h2d_log("ChangeLevelButton: target not set or not a string. Ignoring...");
        actor.game().destroy(actor);
        return;
    }
    actor.addBehavior<ChangeLevelButton>(
            static_cast<float>(object.getWidth()) / TILE_SIZE,
            static_cast<float>(object.getHeight()) / TILE_SIZE,
            value.getString());
}

ChangeLevelButton::ChangeLevelButton(float width, float height, const std::string& target):
p_width(width),
p_height(height),
p_target(target)
{}

void ChangeLevelButton::fixedUpdate()
{
    auto mogl = actor().game().getPlugin<mogl::MultimediaOGL>();
    if (mogl->input().isMouseButtonPressed(sf::Mouse::Left))
    {
        auto mouse = mogl->input().getMouseCurrentPosition();
        float mouse_x = (mouse.x / TILE_SIZE) + mogl->getCamera().getPosition().x;
        float mouse_y = (mouse.y / TILE_SIZE) + mogl->getCamera().getPosition().y;
        sf::FloatRect rect (actor().transform().x, actor().transform().y, p_width, p_height);
        if (rect.contains(mouse_x, mouse_y))
        {
            actor().game().getPlugin<GamePlugin>()->changeLevel(p_target);
        }
    }
}
