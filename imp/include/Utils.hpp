#ifndef IMP_UTILS_HPP
#define IMP_UTILS_HPP

#include <string>
#include "MeshData.hpp"

namespace imp
{

void generateQuad(MeshData& result);

std::string loadShader(const std::string& fileName);

}

#endif // IMP_UTILS_HPP
