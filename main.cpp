#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>
#include "Hum2D/Hum2D.hpp"
#include "Drawable.hpp"
#include "MultimediaOGL.hpp"
#include "Shader.hpp"
#include "ShaderManager.hpp"

class Rectangle : public Drawable
{
public:
    Rectangle()
    {
        if (!s_shaders_init)
        {
            s_shaders_init = true;
            s_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
            char vs[] = "\
layout (location = 0) in vec3 vertex;\
layout (location = 1) in vec4 color;\
\
uniform mat4 ModelMatrix;\
uniform mat4 ViewMatrix;\
uniform mat4 ProjectionMatrix;\
\
out vec4 frontColor;\
\
void main()\
{\
    frontColor = color;\
    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(vertex.xyz, 1.0);\
}\
";
            glShaderSource(s_vertex_shader, 1, &vs, NULL);
            glCompileShader(s_vertex_shader);

            s_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
            char fs[] = "\
in vec4 color;\
out vec4 fragColor;\
void main()\
{\
    fragColor = color;\
}\
";
            glShaderSource(s_fragment_shader, 1, &fs, NULL);
            glCompileShader(s_fragment_shader);
        }
        ShaderId* s = new ShaderId{s_vertex_shader};
        p_shader.addShader(s);
        delete s;
        s = new ShaderId{s_fragment_shader};
        p_shader.addShader(s);
        delete s;
        p_shader.link();

        GLuint VBO_pos, VBO_col;
        glm::vec3 pos[4] = {
            glm::vec3(-0.5, 0.5, 0.0),
            glm::vec3(0.5, 0.5, 0.0),
            glm::vec3(-0.5, -0.5, 0.0),
            glm::vec3(0.5, -0.5, 0.0)
        };

        glm::vec4 col[4] = {
            glm::vec4(0.5, 0.5, 0.0, 1.0),
            glm::vec4(0.5, 0.5, 0.0, 1.0),
            glm::vec4(0.5, 0.5, 0.0, 1.0),
            glm::vec4(0.5, 0.5, 0.0, 1.0)
        };

        glGenVertexArrays(1, &p_VAO);
        glBinVertexArray(p_VAO);

        glGenBuffers(1, &VBO_pos);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_pos);
        glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        glGenBuffers(1, &VBO_col);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_col);
        glBufferData(GL_ARRAY_BUFFER, sizeof(col), col, GL_STATIC_DRAW);

        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
    }

    virtual unsigned int vertexCount() const override
    {
        return 4;
    }

private:
    static bool s_shaders_init;
    static GLuint s_vertex_shader;
    static GLuint s_fragment_shader;
};
bool Rectangle::s_shaders_init = false;
GLuint Rectangle::s_vertex_shader;
GLuint Rectangle::s_fragment_shader;


int main()
{
    h2d::Game g(60);
    auto mogl = g.addPlugin<MultimediaOGL>(sf::VideoMode(800, 600), "OpenGL");

    mogl->setProjection(glm::ortho(2, 2, 2, 2));
    mogl->setView(glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0)));

    auto a = g.makeActor();
    a->addBehaviour<Rectangle>();

    g.run();
}
