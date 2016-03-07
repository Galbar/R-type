#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "Hum2D/Hum2D.hpp"
#include "Shader.hpp"
#include <SFML/OpenGL.hpp>

class Drawable : public h2d::Behaviour
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
	const Shader& shader() const;
	Shader& shader();
	GLuint& VAO();
	const GLuint& VAO() const;
	virtual unsigned int vertexCount() const =0;

private:
	bool p_is_enabled;
	h2d::Transformation p_transform;

protected:
	GLuint p_VAO;
	Shader p_shader;
};

#endif