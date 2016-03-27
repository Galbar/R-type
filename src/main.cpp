#include "Hum2D/Hum2D.hpp"
#include "MOGL/MOGL.hpp"

class OnMouse : public h2d::Behavior
{
public:
    void init() override
    {
        p_input = &actor().game().getPlugin<mogl::MultimediaOGL>()->input();
    }

    void fixedUpdate() override
    {
        actor().transform().x = (p_input->getMouseCurrentPosition().x) * (80./600.) - 40;
        actor().transform().y = (p_input->getMouseCurrentPosition().y) * (80./600.) - 40;
    }

private:
    mogl::InputHandler* p_input;
};

int main(void)
{
    h2d::Game g(60);
    sf::ContextSettings settings;
    settings.antialiasingLevel = 2;
    settings.depthBits = 24;
    settings.majorVersion = 3;
    settings.minorVersion = 3;
    sf::Texture tex;
    tex.loadFromFile("./warrior_cat.jpg");
    sf::Texture tex2;
    tex2.loadFromFile("./sprites.png");
    mogl::MultimediaOGL* mogl = g.addPlugin<mogl::MultimediaOGL>(sf::VideoMode(600, 600), "Test", sf::Style::Default, settings);
    g.addPlugin<h2d::KinematicWorld>();
    //mogl->getCamera().setPerspective(100.f, 1.f);
    mogl->getCamera().setOrthogonal(-40.f, 40.f, -40.f, 40.f);
    mogl->getCamera().setPosition(glm::vec3(0, 0, -1));
    mogl->getCamera().setCenter(glm::vec3(0, 0, 1));
    //mogl->getCamera().setUp(glm::vec3(0, 1, 0));
    h2d::Kinematic* k;
    h2d::Actor* a = g.makeActor();
    sf::Color c;
    c = sf::Color::Cyan;
    c.a = 127;
    auto rect = a->addBehavior<mogl::Rectangle>(2, 30, c);
    rect->setOrigin(glm::vec3(1, 2.5, 0));
    a->transform().z = 20;
    a->transform().rotation = 120;
    k = a->addBehavior<h2d::Kinematic>();
    //k->velocity().x = 2.5;
    //k->velocity().y = 2.5;
    k->velocity().rotation = 360./60.;
    a = g.makeActor();
    c = sf::Color::Magenta;
    c.a = 127;
    rect = a->addBehavior<mogl::Rectangle>(3, 20, c);
    rect->setOrigin(glm::vec3(1.5, 2.5, 0));
    a->transform().z = 11;
    a->transform().rotation = -120;
    k = a->addBehavior<h2d::Kinematic>();
    //k->velocity().x = 5;
    //k->velocity().y = 5;
    k->velocity().rotation = 360./60.;
    a = g.makeActor();
    c = sf::Color::Yellow;
    c.a = 127;
    rect = a->addBehavior<mogl::Rectangle>(4, 10, c);
    rect->setOrigin(glm::vec3(2, 2.5, 0));
    a->transform().z = 12;
    a->transform().rotation = 0;
    k = a->addBehavior<h2d::Kinematic>();
    //k->velocity().x = 5;
    //k->velocity().y = 5;
    k->velocity().rotation = 360./60.;
    a = g.makeActor();
    a->addBehavior<mogl::Sprite>(20, 20, &tex);
    a->transform().z = 50;
    k = a->addBehavior<h2d::Kinematic>();
    //k->velocity().x = 1.25;
    //k->velocity().y = 1.25;
    //k->velocity().rotation = 10;
    a = g.makeActor();
    mogl::SpriteAnimation animation {
        &tex2,
        0, 0, 0, 0, 48, 48,
        {0, 1, 2, 3, 5, 6, 7, 8},
        std::vector<h2d::Time>(8, h2d::Time::milliseconds(300))
    };
    a->transform().z = 15;
    auto anim = a->addBehavior<mogl::AnimatedSprite>(20, 20, &animation);
    anim->setOrigin(glm::vec3(10, 10, 0));
    k = a->addBehavior<h2d::Kinematic>();
    a->addBehavior<OnMouse>();
    //k->velocity().x = 1.25;
    //k->velocity().y = 1.25;
    //k->velocity().rotation = 10;
    g.run();
    return 0;
}
