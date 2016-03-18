#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "Hum2D/Hum2D.hpp"
#include "ShaderProgram.hpp"
#include <SFML/OpenGL.hpp>

class Drawable : public h2d::Behavior
{
public:
    Drawable();
    virtual ~Drawable();

    virtual void init() override;
    virtual void onDestroy() override;

    void enable();
    void disable();
    bool isEnabled() const;

    h2d::Transformation& transform();
    const h2d::Transformation& transform() const;
    const ShaderProgram* shaderProgram() const;
    ShaderProgram* shaderProgram();
    virtual void draw() =0;

private:
    bool p_is_enabled;
    h2d::Transformation p_transform;

protected:
    ShaderProgram* p_shader_program;
};

#endif
