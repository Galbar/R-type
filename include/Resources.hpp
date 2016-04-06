#ifndef RESOURCES_LOAD
#define RESOURCES_LOAD
#include <fstream>
#include <sstream>
#include "MOGL/MOGL.hpp"

void readFileContents(const std::string& filename, std::stringstream& ss);
void loadAnimation(mogl::MultimediaOGL& mogl, const std::string& animation_name, const std::string& filename);
void loadResources(mogl::MultimediaOGL& mogl, const std::string& resources_filename);
#endif

