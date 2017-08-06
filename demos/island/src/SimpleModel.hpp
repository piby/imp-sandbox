#ifndef SIMPLE_MODEL
#define SIMPLE_MODEL

#include <string>
#include <vector>

#include "VertexBuffer.hpp"
#include "VertexArray.hpp"

namespace tinygltf
{
    class Model;
}

class SimpleModel
{
public:

    SimpleModel();

    void create(const tinygltf::Model& model);

    void draw();

protected:

    unsigned int m_vertexCount;
    imp::VertexArray m_vao;
    std::vector<imp::VertexBuffer> m_vertexBuffers;
};

#endif // SIMPLE_MODEL
