#include "SimpleMesh.hpp"

using namespace imp;

struct AttributeComponentData
{
    unsigned int sizeInBytes;
    VertexArray::DataType vaoDataType;
};

static std::map<SimpleMesh::Components, AttributeComponentData > ComponentData =
{
    { SimpleMesh::Components::POSITION,    { 3 * sizeof( float ), VertexArray::DataType::FLOAT_3_COMPONENTS }},
    { SimpleMesh::Components::NORMAL,      { 3 * sizeof( float ), VertexArray::DataType::FLOAT_3_COMPONENTS }},
    { SimpleMesh::Components::TEX_COORD_0, { 2 * sizeof( float ), VertexArray::DataType::FLOAT_2_COMPONENTS }},
    { SimpleMesh::Components::TEX_COORD_1, { 2 * sizeof( float ), VertexArray::DataType::FLOAT_2_COMPONENTS }},
    { SimpleMesh::Components::TEX_COORD_2, { 2 * sizeof( float ), VertexArray::DataType::FLOAT_2_COMPONENTS }},
    { SimpleMesh::Components::TEX_COORD_3, { 2 * sizeof( float ), VertexArray::DataType::FLOAT_2_COMPONENTS }},
    //{ SimpleMesh::Components::ARRAYTEXCOORD_0, ...
};


SimpleMesh::SimpleMesh()
    : m_indicesCount(0)
{
}


void SimpleMesh::create( const Data& data )
{
    m_indicesCount = data.indicesCount;

    // calculate size of data for single vertex
    unsigned int striteBytes = 0;
    for( auto component : data.components )
    {
        striteBytes += ComponentData[component].sizeInBytes;
    }

    // create VBO with mesh indices
    m_indicesVBO.create(
        VertexBuffer::Type::INDEX_DATA,
        VertexBuffer::UsageFlag::SPECIFIED_ONCE,
        data.indices.size(), data.indices.data());

    // create VBO with vertex attributes
    m_attributesVBO.create(
        VertexBuffer::Type::VERTEX_DATA,
		VertexBuffer::UsageFlag::SPECIFIED_ONCE,
        data.attributes.size(), data.attributes.data());

    // create VAO
    m_vao.create();
    m_vao.bind();
    m_attributesVBO.bind();

    // specify vertex attributes
    unsigned int attributeIndex = 0;
    unsigned int offsetBytes = 0;
    for( auto component : data.components )
    {
        m_vao.setFloatAttribute(
            attributeIndex,
            ComponentData[component].vaoDataType,
            offsetBytes,
            striteBytes);
        m_vao.setAttributeUsage(attributeIndex, true);

        offsetBytes += ComponentData[component].sizeInBytes;
        ++attributeIndex;
    }

    m_indicesVBO.bind();
    m_vao.unbind();
}


void SimpleMesh::draw()
{
    assert( m_indicesCount != 0 );

    m_vao.bind();

    glDrawElements(GL_TRIANGLE_STRIP, m_indicesCount, GL_UNSIGNED_INT, 0);

    m_vao.unbind();
}
