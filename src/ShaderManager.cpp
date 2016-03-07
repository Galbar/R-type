#include "ShaderManager.hpp"

ShaderId* ShaderManager::loadResource(const ShaderData& data)
{
    ShaderId* shader = new ShaderId();

    shader->id = glCreateShader(data.type == VERTEX_SHADER ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
    const char* src = data.source.c_str();
    glShaderSource(shader->id, 1, &src, NULL);
    glCompileShader(shader->id);
    GLint compiled;
    glGetShaderiv(shader->id, GL_COMPILE_STATUS, compiled);
    if (compiled)
    {
        return shader;
    }
    delete shader;
    return nullptr;
}
