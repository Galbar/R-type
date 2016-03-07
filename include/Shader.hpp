#ifndef SHADER_HPP
#define SHADER_HPP

#include <SFML/OpenGL.hpp>
#include "ShaderManager.hpp"

class Shader
{
public:
    Shader();
    ~Shader();

    void addShader(ShaderId* shader);
    void link();
    void bind() const;
    GLuint programId() const;

    GLuint modelMatrixLocation() const;
    GLuint viewMatrixLocation() const;
    GLuint projectionMatrixLocation() const;

private:
    GLuint p_program;
    GLuint p_model_matrix;
    GLuint p_view_matrix;
    GLuint p_projection_matrix;
    ShaderId p_vertex_shader;
    ShaderId p_fragment_shader;
};

#endif
