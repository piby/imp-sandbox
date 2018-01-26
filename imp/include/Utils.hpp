#ifndef IMP_UTILS_HPP
#define IMP_UTILS_HPP

#include <string>
#include "MeshData.hpp"

namespace imp
{

struct Size
{
	GLsizei width;
	GLsizei height;
};

struct Rectangle
{
	unsigned short llxCorner;
	unsigned short llyCorner;
	GLsizei width;
	GLsizei height;
};

void generateQuad(MeshData& result);

std::string loadShader(const std::string& fileName);

}

#endif // IMP_UTILS_HPP
