#include "Utils.hpp"
#include <vector>
#include <fstream>
#include <cstring>
#include <GL/glew.h>

using namespace imp;

void imp::generateQuad(MeshData& result)
{
    std::vector<float> quadAttributes =
    {
        -1.0f,  1.0f, 0.0f,  // vert 0
         0.0f, 1.0f,         // uv 0
        -1.0f, -1.0f, 0.0f,  // vert 1
         0.0f, 0.0f,         // uv 1
         1.0f,  1.0f, 0.0f,  // vert 2
         1.0f, 1.0f,         // uv 2
         1.0f, -1.0f, 0.0f,  // vert 3
         1.0f, 0.0f          // uv 3
    };
    std::size_t attributeBytes = quadAttributes.size() * sizeof(float);

    result.drawMode = GL_TRIANGLE_STRIP;

    result.indicesCount = 4;
    result.indicesType = GL_UNSIGNED_BYTE;
    result.indicesData.clear();
    result.indicesData.reserve(4);
    result.indicesData = { 0, 1, 2, 3 };

    result.attributes.clear();
    result.attributes = { MeshData::Attribute::POSITION, MeshData::Attribute::TEX_COORD_0 };

    result.vertexCount = 4;
    result.attributesData.clear();
    result.attributesData.assign(attributeBytes, 0);
    std::memcpy(result.attributesData.data(), quadAttributes.data(), attributeBytes);

    result.boundingBoxMin = {-1.0f, -1.0f, 0.0f, 0.0f };
    result.boundingBoxMax = { 1.0f,  1.0f, 0.0f, 0.0f };

    result.textures.clear();
}


std::string imp::loadShader(const std::string& fileName)
{
    std::ifstream shaderFile(fileName.c_str());
    if (!shaderFile.is_open())
    {
        return std::string();
    }

    shaderFile.seekg (0, shaderFile.end);
    long size = shaderFile.tellg();
    shaderFile.seekg (0, shaderFile.beg);
    if (!size)
    {
        shaderFile.close();
        return std::string();
    }

    std::vector<GLchar> buffer(static_cast<unsigned long>(size));
    shaderFile.read(&buffer[0], size);
    shaderFile.close();

    return &buffer[0];
}
