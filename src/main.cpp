#include "main.hpp"

int main(void)
{
    h2d::Game game(60);
    game.addPlugin<h2d::KinematicWorld>();
    ActorFactory factory;
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

    game.addPlugin<GamePlugin>()->setCameraSpeed(0.5);

    mogl->textures().load("sprites", "./sprites.png");

    auto a = game.makeActor();
    mogl::SpriteAnimation anim {
        mogl->textures().get("sprites"),
        0, 0, 0, 0, 48, 48,
        {0,1,2,3,5,6,7,8},
        std::vector<h2d::Time>(8, h2d::Time::milliseconds(300))
    };

    mogl->spriteAnimations().load("player_anim", anim);

    factory.build("Player", *a, tiled::Object());

    a = game.makeActor();
    a->addBehavior<mogl::Rectangle>(2, 2, sf::Color::Red);
    a->addBehavior<Collider>(2, 2, Collider::Type::Wall);
    a->transform().x = 10;
    a->transform().y = 10;

    game.run();
    return 0;
}
