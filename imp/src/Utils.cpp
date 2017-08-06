#include "Utils.hpp"
#include <vector>
#include <fstream>
#include <GL/glew.h>


std::string imp::loadShader(const std::string& fileName)
{
    std::ifstream shaderFile(fileName.c_str());
	if (!shaderFile.is_open())
	{
		return std::string();
	}

	shaderFile.seekg (0, shaderFile.end);
	int size = shaderFile.tellg();
	shaderFile.seekg (0, shaderFile.beg);
	if (!size)
	{
		shaderFile.close();
		return std::string();
	}

	std::vector<GLchar> buffer(size);
	shaderFile.read(&buffer[0], size);
	shaderFile.close();

	return &buffer[0];
}
