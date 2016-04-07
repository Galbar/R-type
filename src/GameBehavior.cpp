#include "GameBehavior.hpp"
#include "GamePlugin.hpp"
#include "Defines.hpp"

GamePlugin* GameBehavior::s_p_game_pl = nullptr;
mogl::MultimediaOGL* GameBehavior::s_p_mogl = nullptr;

void GameBehavior::init()
{
    if (s_p_game_pl == nullptr)
    {
        s_p_game_pl = actor().game().getPlugin<GamePlugin>();
    }
    if (s_p_mogl == nullptr)
    {
        s_p_mogl = actor().game().getPlugin<mogl::MultimediaOGL>();
    }
}

void GameBehavior::fixedUpdate()
{
    if (actor().transform().x < s_p_mogl->getCamera().getPosition().x - 3
            or actor().transform().x > s_p_mogl->getCamera().getPosition().x + ORTHO_WIDTH + 5
            or actor().transform().y < s_p_mogl->getCamera().getPosition().y - 3
            or actor().transform().y > s_p_mogl->getCamera().getPosition().y + ORTHO_HEIGHT + 3)
    {
        actor().game().destroy(actor());
    }
}
