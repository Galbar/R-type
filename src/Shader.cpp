#include "Shader.hpp"

Shader::Shader()
{
    p_program = glCreateProgram();
}

Shader::~Shader()
{}

void Shader::addShader(ShaderId* shader)
{
    glAttachShader(p_program, shader->id);
}

void Shader::link()
{
    glLinkProgram(p_program);
    p_model_matrix = glGetUniformLocation(p_program, "ModelMatrix");
    p_view_matrix = glGetUniformLocation(p_program, "ViewMatrix");
    p_projection_matrix = glGetUniformLocation(p_program, "ProjectionMatrix");
}

void Shader::bind() const
{
    glUseProgram(p_program);
}

GLuint Shader::programId() const
{
    return p_program;
}

GLuint Shader::modelMatrixLocation() const
{
    return p_model_matrix;
}

GLuint Shader::viewMatrixLocation() const
{
    return p_view_matrix;
}

GLuint Shader::projectionMatrixLocation() const
{
    return p_projection_matrix;
}
