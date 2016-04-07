#include "PlayButton.hpp"

void PlayButtonBuilder::construct(h2d::Actor& actor, const tiled::Object& object)
{
    actor.addBehavior<PlayButton>(
            static_cast<float>(object.getWidth()) / TILE_SIZE,
            static_cast<float>(object.getHeight()) / TILE_SIZE);
}

PlayButton::PlayButton(float width, float height):
p_width(width),
p_height(height)
{}

void PlayButton::fixedUpdate()
{
    auto mogl = actor().game().getPlugin<mogl::MultimediaOGL>();
    if (mogl->input().isMouseButtonPressed(sf::Mouse::Left))
    {
        auto mouse = mogl->input().getMouseCurrentPosition();
        mouse.x /= TILE_SIZE;
        mouse.y /= TILE_SIZE;
        if (mouse.x > actor().transform().x
            and mouse.x < actor().transform().x + p_width
            and mouse.y > actor().transform().y
            and mouse.y < actor().transform().y + p_height)
        {
            actor().game().getPlugin<GamePlugin>()->changeLevel("credits");
        }
    }
}
