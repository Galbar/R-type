#include "Drawable.hpp"
#include "MultimediaOGL.hpp"

Drawable::Drawable():
p_is_enabled(true)
{}

Drawable::~Drawable()
{}

void Drawable::init()
{
    if (p_is_enabled)
    {
        actor().game().getPlugin<MultimediaOGL>()->addDrawable(this);
    }
}

void Drawable::onDestroy()
{
    disable();
}

void Drawable::enable()
{
    if (!p_is_enabled)
    {
        actor().game().getPlugin<MultimediaOGL>()->addDrawable(this);
        p_is_enabled = true;
    }
}

void Drawable::disable()
{
    if (p_is_enabled)
    {
        actor().game().getPlugin<MultimediaOGL>()->removeDrawable(this);
        p_is_enabled = false;
    }
}

bool Drawable::isEnabled() const
{
    return p_is_enabled;
}

h2d::Transformation& Drawable::transform()
{
    return p_transform;
}

const h2d::Transformation& Drawable::transform() const
{
    return p_transform;
}

Shader& Drawable::shader()
{
    return p_shader;
}

const Shader& Drawable::shader() const
{
    return p_shader;
}

GLuint& Drawable::VAO()
{
    return p_VAO;
}

const GLuint& Drawable::VAO() const
{
    return p_VAO;
}
