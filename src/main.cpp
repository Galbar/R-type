#include "main.hpp"

int main(void)
{
    h2d::Game game(60);
    game.addPlugin<h2d::KinematicWorld>();
    ActorFactory factory;

    // Add here the actor builders
    factory.set<PlayerBuilder>("Player");

    sf::ContextSettings settings;
    settings.antialiasingLevel = 2;
    settings.depthBits = 24;
    settings.majorVersion = 3;
    settings.minorVersion = 3;
    mogl::MultimediaOGL* mogl = game.addPlugin<mogl::MultimediaOGL>(
            sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Test",
            sf::Style::Default, settings);
    mogl->getCamera().setOrthogonal(0, -ORTHO_WIDTH, ORTHO_HEIGHT, 0);
    mogl->getCamera().setPosition(glm::vec3(0, 0, -1));
    mogl->getCamera().setCenter(glm::vec3(0, 0, 1));
    mogl->getCamera().setUp(glm::vec3(0, 1, 0));

    auto game_pl = game.addPlugin<GamePlugin>();
    game_pl->setActorFactory(factory);
    game_pl->setCameraSpeed(1.5);

    game.run();
    return 0;
}
