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
        actor().transform().y = -(p_input->getMouseCurrentPosition().y) * (80./600.) + 40;
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
    glEnable(GL_DEPTH_TEST);
    g.addPlugin<h2d::KinematicWorld>();
    //mogl->setProjection(glm::perspective(90.f, 1.f, 0.1f, 100.0f));
    mogl->setProjection(glm::ortho(-40.f, 40.f, -40.f, 40.f, 0.1f, 100.f));
    mogl->setView(glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0)));
    h2d::Kinematic* k;
    h2d::Actor* a = g.makeActor();
    sf::Color c;
    c = sf::Color::Magenta;
    c.a = 127;
    a->addBehavior<mogl::Rectangle>(20, 20, c);
    a->transform().z = -10;
    k = a->addBehavior<h2d::Kinematic>();
    //k->velocity().x = 5;
    //k->velocity().y = 5;
    k->velocity().rotation = 45;
    a = g.makeActor();
    c = sf::Color::Cyan;
    c.a = 127;
    a->addBehavior<mogl::Rectangle>(30, 10, c);
    a->transform().z = -20;
    k = a->addBehavior<h2d::Kinematic>();
    //k->velocity().x = 2.5;
    //k->velocity().y = 2.5;
    k->velocity().rotation = -45;
    a = g.makeActor();
    a->addBehavior<mogl::Sprite>(20, 20, &tex);
    a->transform().z = -0;
    k = a->addBehavior<h2d::Kinematic>();
    //k->velocity().x = 1.25;
    //k->velocity().y = 1.25;
    //k->velocity().rotation = 10;
    a = g.makeActor();
    mogl::SpriteAnimation animation {
        &tex2,
        0, 0, 0, 0, 48, 48,
        {0, 1, 2, 3, 5, 6, 7, 8},
        std::vector<h2d::Time>(8, h2d::Time::milliseconds(500))
    };
    a->addBehavior<mogl::AnimatedSprite>(20, 20, &animation);
    a->transform().x = 30;
    a->transform().y = 30;
    k = a->addBehavior<h2d::Kinematic>();
    a->addBehavior<OnMouse>();
    //k->velocity().x = 1.25;
    //k->velocity().y = 1.25;
    //k->velocity().rotation = 10;
    g.run();
    return 0;
}
