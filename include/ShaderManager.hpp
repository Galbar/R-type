#ifndef SHADERMANAGER_HPP
#define SHADERMANAGER_HPP

#include "Hum2D/ResourceManager.hpp"
#include <SFML/OpenGL.hpp>

enum ShaderType { VERTEX_SHADER, FRAGMENT_SHADER };

struct ShaderId
{
	GLuint id;
};

struct ShaderData
{
	std::string source;
	ShaderType type;
};

class ShaderManager : public h2d::ResourceManager<ShaderId, std::string, ShaderData>
{
protected:
	virtual ShaderId* loadResource(const ShaderData& data);
};

#endif