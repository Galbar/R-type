#include "Hum2D/Hum2D.hpp"
#include "MultimediaOGL.hpp"
#include "Drawable.hpp"
#include "glm/glm.hpp"

class rect : public Drawable
{
public:
    rect (double width, double height)
    {
        Shader v_shader, f_shader;
        v_shader.loadFromFile(Shader::Type::VERTEX_SHADER, "rect.vert");
        f_shader.loadFromFile(Shader::Type::FRAGMENT_SHADER, "rect.frag");
        p_shader_program = new ShaderProgram();

        p_shader_program
            ->addShader(v_shader)
            ->addShader(f_shader)
            ->link();

        float x = width/2;
        float y = height/2;
        float vert[24] = {-x, y, -x, -y, x, -y,
                          x, -y,  x,  y, -x, y};

        glGenVertexArrays(1, &p_VAO);
        glBindVertexArray(p_VAO);
        glGenBuffers(1, &p_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, p_VBO);
        glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vert, GL_STATIC_DRAW);
        p_position_loc = p_shader_program->bindVertexAttribute("position", 2, 0, 0);
    }

    void init() override
    {
        enable();
    }

    virtual ~rect ()
    {
        glDeleteBuffers(1, &p_VBO);
        delete p_shader_program;
    }

    virtual void draw() override
    {
        glBindVertexArray(p_VAO);
        glEnableVertexAttribArray(p_position_loc);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

private:
    GLuint p_VAO, p_VBO, p_position_loc;
};

int main(void)
{
    h2d::Game g(60);
    MultimediaOGL* mogl = g.addPlugin<MultimediaOGL>(sf::VideoMode(600, 600), "Test");
    h2d::Actor* a = g.makeActor();
    a->addBehavior<rect>(300, 300);
    mogl->setProjection(glm::ortho(-300, 300, -300, 300, -100, 100));
    g.run();
    return 0;
}
