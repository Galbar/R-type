#include "MultimediaOGL.hpp"

MultimediaOGL::MultimediaOGL(sf::VideoMode mode, const sf::String& title, sf::Uint32 style, const sf::ContextSettings& settings):
p_window(new sf::Window(mode, title, style, settings))
{}

MultimediaOGL::~MultimediaOGL()
{
    delete p_window;
}

void MultimediaOGL::preFixedUpdate()
{
    sf::Event event;
    while (p_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            p_window->close();
            game().setRunning(false);
        }
    }
}

void MultimediaOGL::postUpdate()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (auto it : p_shader_program_usage)
    {
        it.first->setUniformMatrix4f("projection", p_projection);
    }

    for (Drawable* drawable : p_drawable_set)
    {
        h2d_assert(drawable->shaderProgram() != nullptr, "Found a drawable without a shader program");

        glm::mat4 model(1.0);
        model = glm::translate(model, glm::vec3(drawable->transform().x, drawable->transform().y, drawable->transform().z));
        model = glm::rotate(model, glm::radians(static_cast<float>(drawable->transform().rotation)), glm::vec3(0., 0., 1.));
        model = glm::scale(model, glm::vec3(drawable->transform().scale_x, drawable->transform().scale_y, 1.));
        model = p_view * model;
        drawable->shaderProgram()->setUniformMatrix4f("modelview", model);
        drawable->draw();
    }
    glBindVertexArray(0);
}

sf::Window* MultimediaOGL::window()
{
    return p_window;
}

const sf::Window* MultimediaOGL::window() const
{
    return p_window;
}

void MultimediaOGL::addDrawable(Drawable* drawable)
{
    p_drawable_set.insert(drawable);
    try
    {
        p_drawable_kinematic[drawable] = drawable->actor().getBehavior<h2d::Kinematic>();
    }
    catch (h2d::exception::BehaviorNotFound e)
    {
        p_drawable_kinematic[drawable] = nullptr;
    }

    if (drawable->shaderProgram())
    {
        if (p_shader_program_usage.find(drawable->shaderProgram()) == p_shader_program_usage.end())
        {
            p_shader_program_usage.insert(std::make_pair(drawable->shaderProgram(), 0));
        }

        p_shader_program_usage[drawable->shaderProgram()] += 1;
    }
}

void MultimediaOGL::removeDrawable(Drawable* drawable)
{
    p_drawable_set.erase(drawable);
    p_drawable_kinematic.erase(drawable);

    if (drawable->shaderProgram())
    {
        p_shader_program_usage[drawable->shaderProgram()] -= 1;

        if (p_shader_program_usage[drawable->shaderProgram()] == 0)
        {
            p_shader_program_usage.erase(drawable->shaderProgram());
        }
    }
}

void MultimediaOGL::setProjection(const glm::mat4& projection)
{
    p_projection = projection;
}

void MultimediaOGL::setView(const glm::mat4& view)
{
    p_view = view;
}
