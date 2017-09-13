#ifndef IMP_UTILS_HPP
#define IMP_UTILS_HPP

#include <string>

namespace imp
{

const unsigned int quadIndices[] =
{
	0, 1, 2, 3
};

const unsigned int quadIndicesSize = sizeof(quadIndices);

const float quadData[] =
{
	-1.0f,  1.0f, 0.0f,		// vert 0
	 0.0f, 1.0f,			// uv 0
	-1.0f, -1.0f, 0.0f,		// vert 1
	 0.0f, 0.0f,			// uv 1
	 1.0f,  1.0f, 0.0f,		// vert 2
	 1.0f, 1.0f,			// uv 2
	 1.0f, -1.0f, 0.0f,		// vert 3
	 1.0f, 0.0f 			// uv 3
};

const unsigned int quadDataSize = sizeof(quadData);


std::string loadShader(const std::string& fileName);

}

#endif // IMP_UTILS_HPP
