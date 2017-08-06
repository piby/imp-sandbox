#include "tiny_gltf.h"
#include "SimpleModel.hpp"

using namespace imp;

/*
VertexBuffer modelDataVBO;
VertexBuffer modelIndexVBO;
VertexArray modelVAO;
*/

SimpleModel::SimpleModel()
    : m_vertexCount(0)
{

}

void SimpleModel::create(const tinygltf::Model& model)
{
    // construct vertex buffer objects
    for(const auto& buffer : model.buffers)
    {
        imp::VertexBuffer vbo;
        vbo.allocate(
            VertexBuffer::Type::VERTEX_DATA,
            VertexBuffer::UsageFlag::SPECIFIED_ONCE,
            buffer.data.size(), &buffer.data[0]);
        m_vertexBuffers.push_back(vbo);
    }

    for(const auto& accessor : model.accessors)
    {
        int bufferViewIndex = accessor.bufferView;
        const tinygltf::BufferView& bufferView = model.bufferViews[bufferViewIndex];

        int bufferIndex = bufferView.buffer;
        const tinygltf::Buffer& buffer = model.buffers[bufferIndex];
/*
        imp::VertexBuffer vbo;
        vbo.allocate(
            VertexBuffer::Type::VERTEX_DATA,
            VertexBuffer::UsageFlag::SPECIFIED_ONCE,
            quadDataSize, quadData);
        // ... buffer.data
*/
    }

    /*
    modelDataVBO.allocate(
        VertexBuffer::Type::VERTEX_DATA,
        VertexBuffer::UsageFlag::SPECIFIED_ONCE,
        quadDataSize, quadData);

    modelIndexVBO.allocate(
		VertexBuffer::Type::INDEX_DATA,
		VertexBuffer::UsageFlag::SPECIFIED_ONCE,
		quadIndicesSize, quadIndices);

    modelVAO.create();
    modelVAO.bind();

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    modelDataVBO.bind();
    modelVAO.setFloatAttribute(0, VertexArray::DataType::FLOAT_3_COMPONENTS, 0, 5*sf);
    modelVAO.setFloatAttribute(1, VertexArray::DataType::FLOAT_2_COMPONENTS, 3*sf, 5*sf);
    modelIndexVBO.bind();
    modelVAO.unbind();
    */
}

void SimpleModel::draw()
{
    m_vao.bind();

    glDrawElements(GL_TRIANGLE_STRIP, m_vertexCount, GL_UNSIGNED_INT, 0);

    m_vao.unbind();
}
