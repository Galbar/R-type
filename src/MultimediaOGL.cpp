#include "MultimediaOGL.hpp"
#include <SFML/Graphics.hpp>

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
    for (Drawable* drawable : p_drawable_set)
    {
        drawable->shader().bind();

        glBindVertexArray(drawable->VAO());

        glm::mat4 model(1.f);
        model = glm::translate(model, glm::vec3(drawable->transform().x, drawable->transform().y, drawable->transform().z));
        model = glm::rotate(model, glm::radians(drawable->transform().rotation), glm::vec3(0., 0., 1.));
        model = glm::scale(model, glm::vec3(drawable->transform().scale_x, drawable->transform().scale_y, 1.));
        glUniformMatrix4fv(drawable->shader().modelMatrixLocation(), 1, GL_FALSE, &model[0][0]);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, drawable->vertexCount());
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
        p_drawable_kinematic[drawable] = drawable->actor().getBehaviour<h2d::Kinematic>();
    }
    catch (h2d::exception::BehaviourNotFound e)
    {
        p_drawable_kinematic[drawable] = nullptr;
    }
}

void MultimediaOGL::removeDrawable(Drawable* drawable)
{
    p_drawable_set.erase(drawable);
    p_drawable_kinematic.erase(drawable);
}

void MultimediaOGL::setProjection(const glm::mat4& projection)
{
    p_projection = projection;
    for (Drawable* drawable : p_drawable_set)
    {
        glUniformMatrix4fv(drawable->shader().projectionMatrixLocation(), 1, GL_FALSE, &projection[0][0]);
    }
}

void MultimediaOGL::setView(const glm::mat4& view)
{
    p_view = view;
    for (Drawable* drawable : p_drawable_set)
    {
        glUniformMatrix4fv(drawable->shader().viewMatrixLocation(), 1, GL_FALSE, &view[0][0]);
    }
}
