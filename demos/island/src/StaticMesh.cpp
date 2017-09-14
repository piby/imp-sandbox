#include "StaticMesh.hpp"

using namespace imp;

struct AttributeComponentData
{
	unsigned int sizeInBytes;
	VertexArray::DataType vaoDataType;
};

static std::map<MeshData::Attribute, AttributeComponentData > ComponentData =
{
	{ MeshData::Attribute::POSITION,	{ 3 * sizeof( float ), VertexArray::DataType::FLOAT_3_COMPONENTS }},
	{ MeshData::Attribute::NORMAL,		{ 3 * sizeof( float ), VertexArray::DataType::FLOAT_3_COMPONENTS }},
	{ MeshData::Attribute::TANGENT,		{ 3 * sizeof( float ), VertexArray::DataType::FLOAT_3_COMPONENTS }},
	{ MeshData::Attribute::TEX_COORD_0, { 2 * sizeof( float ), VertexArray::DataType::FLOAT_2_COMPONENTS }},
	{ MeshData::Attribute::TEX_COORD_1, { 2 * sizeof( float ), VertexArray::DataType::FLOAT_2_COMPONENTS }},
	{ MeshData::Attribute::TEX_COORD_2, { 2 * sizeof( float ), VertexArray::DataType::FLOAT_2_COMPONENTS }},
	{ MeshData::Attribute::TEX_COORD_3, { 2 * sizeof( float ), VertexArray::DataType::FLOAT_2_COMPONENTS }},
	//{ MeshData::Components::ARRAYTEXCOORD_0, ...
};


StaticMesh::StaticMesh()
	: m_indicesCount(0)
{
}


void StaticMesh::create( const imp::MeshData& data )
{
	m_indicesCount = data.indicesCount;
	m_indicesType = data.indicesType;
	m_drawMode = data.drawMode;

	// calculate size of data for single vertex
	unsigned int striteBytes = 0;
	for( auto component : data.attributes )
	{
		striteBytes += ComponentData[component].sizeInBytes;
	}

	// create VBO with mesh indices
	m_indicesVBO.create(
		BufferType::INDEX_DATA,
		BufferUsageFlag::SPECIFIED_ONCE,
		data.indicesData.size(), data.indicesData.data());

	// create VBO with vertex attributes
	m_attributesVBO.create(
		BufferType::VERTEX_DATA,
		BufferUsageFlag::SPECIFIED_ONCE,
		data.attributesData.size(), data.attributesData.data());

	// create VAO
	m_vao.create();
	m_vao.bind();
	m_attributesVBO.bind();

	// specify vertex attributes
	unsigned int attributeIndex = 0;
	unsigned int offsetBytes = 0;
	for( auto component : data.attributes )
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


void StaticMesh::draw() const
{
	assert( m_indicesCount != 0 );

	m_vao.bind();

	glDrawElements(m_drawMode, m_indicesCount, m_indicesType, 0);

	m_vao.unbind();
}
