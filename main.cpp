#include "Hum2D/Hum2D.hpp"
#include <SFML/Graphics.hpp>
#include "MultimediaOGL.hpp"
#include "Drawable.hpp"
#include "glm/glm.hpp"

class rect : public Drawable
{
public:
    rect (double width, double height, sf::Texture* texture):
    p_width(width),
    p_height(height),
    p_tex(texture)
    {}

    virtual ~rect ()
    {
        glDeleteBuffers(1, &p_VBO);
        delete p_shader_program;
    }

    void init() override
    {
        Shader v_shader, f_shader;
        bool loaded = v_shader.loadFromFile(Shader::Type::VERTEX_SHADER, "rect.vert");
        h2d_assert(loaded, "vertex shader not loaded");
        loaded = f_shader.loadFromFile(Shader::Type::FRAGMENT_SHADER, "rect.frag");
        h2d_assert(loaded, "fragment shader not loaded");
        p_shader_program = new ShaderProgram();

        p_shader_program
            ->addShader(v_shader)
            ->addShader(f_shader)
            ->link()
            ->bindFragmentOutput("out_color");
        h2d_assert(p_shader_program->isLinked(), "Shader program linking error:"
                << std::endl
                << p_shader_program->log());

        float x = p_width/2;
        float y = p_height/2;
        //float vert[12] = {-x, -y, -x, y, x, y,
        //                  -x, -y,  x, y, x, -y};
        float vert[12] = {-x, -y, x, y, -x, y,
                          -x, -y,  x, -y, x, y};

        glGenVertexArrays(1, &p_VAO);
        glBindVertexArray(p_VAO);
        glGenBuffers(1, &p_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, p_VBO);
        glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vert, GL_STATIC_DRAW);
        p_position_loc = p_shader_program->bindVertexAttribute("position", 2, 0, 0);
        Drawable::init();
    }

    virtual void draw() override
    {
        glEnable(GL_TEXTURE_2D);
        sf::Texture::bind(p_tex);
        glBindVertexArray(p_VAO);
        glEnableVertexAttribArray(p_position_loc);
        h2d_log_d("hai");
        glDrawArrays(GL_TRIANGLES, 0, 6);
        h2d_log_d("hai2");
        sf::Texture::bind(NULL);
        glDisable(GL_TEXTURE_2D);
    }

private:
    GLuint p_VAO, p_VBO, p_position_loc;
    float p_width, p_height;
    sf::Texture* p_tex;
};

int main(void)
{
    h2d::Game g(60);
    sf::ContextSettings settings;
    settings.majorVersion = 3;
    settings.minorVersion = 3;
    MultimediaOGL* mogl = g.addPlugin<MultimediaOGL>(sf::VideoMode(600, 600), "Test", sf::Style::Default, settings);
    g.addPlugin<h2d::KinematicWorld>();
    h2d::Actor* a = g.makeActor();
    sf::Texture tex;
    tex.loadFromFile("warrior_cat.jpg");
    a->addBehavior<rect>(20, 20, &tex);
    auto k = a->addBehavior<h2d::Kinematic>();
    k->velocity().x = 5;
    k->velocity().y = 5;
    k->velocity().rotation = 45;
    mogl->setProjection(glm::ortho(-40.f, 40.f, -40.f, 40.f, 0.1f, 100.f));
    mogl->setView(glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0)));
    g.run();
    return 0;
}
