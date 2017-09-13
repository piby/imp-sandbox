#include <assert.h>

struct AttributeData
{
	int type;
	int components;
};

static std::map<VertexArray::DataType, AttributeData> FormatData =
{
	{ VertexArray::DataType::BYTE_1_COMPONENT,				{GL_BYTE, 1} },
	{ VertexArray::DataType::BYTE_2_COMPONENTS,				{GL_BYTE, 2} },
	{ VertexArray::DataType::BYTE_3_COMPONENTS,				{GL_BYTE, 3} },
	{ VertexArray::DataType::BYTE_4_COMPONENTS,				{GL_BYTE, 4} },

	{ VertexArray::DataType::UNSIGNED_BYTE_1_COMPONENT,		{GL_UNSIGNED_BYTE, 1} },
	{ VertexArray::DataType::UNSIGNED_BYTE_2_COMPONENTS,	{GL_UNSIGNED_BYTE, 2} },
	{ VertexArray::DataType::UNSIGNED_BYTE_3_COMPONENTS,	{GL_UNSIGNED_BYTE, 3} },
	{ VertexArray::DataType::UNSIGNED_BYTE_4_COMPONENTS,	{GL_UNSIGNED_BYTE, 4} },

	{ VertexArray::DataType::SHORT_1_COMPONENT,				{GL_SHORT, 1} },
	{ VertexArray::DataType::SHORT_2_COMPONENTS,			{GL_SHORT, 2} },
	{ VertexArray::DataType::SHORT_3_COMPONENTS,			{GL_SHORT, 3} },
	{ VertexArray::DataType::SHORT_4_COMPONENTS,			{GL_SHORT, 4} },

	{ VertexArray::DataType::UNSIGNED_SHORT_1_COMPONENT,	{GL_UNSIGNED_SHORT, 1} },
	{ VertexArray::DataType::UNSIGNED_SHORT_2_COMPONENTS,	{GL_UNSIGNED_SHORT, 2} },
	{ VertexArray::DataType::UNSIGNED_SHORT_3_COMPONENTS,	{GL_UNSIGNED_SHORT, 3} },
	{ VertexArray::DataType::UNSIGNED_SHORT_4_COMPONENTS,	{GL_UNSIGNED_SHORT, 4} },

	{ VertexArray::DataType::INT_1_COMPONENT,				{GL_INT, 1} },
	{ VertexArray::DataType::INT_2_COMPONENTS,				{GL_INT, 2} },
	{ VertexArray::DataType::INT_3_COMPONENTS,				{GL_INT, 3} },
	{ VertexArray::DataType::INT_4_COMPONENTS,				{GL_INT, 4} },

	{ VertexArray::DataType::UNSIGNED_INT_1_COMPONENT,		{GL_UNSIGNED_INT, 1} },
	{ VertexArray::DataType::UNSIGNED_INT_2_COMPONENTS,		{GL_UNSIGNED_INT, 2} },
	{ VertexArray::DataType::UNSIGNED_INT_3_COMPONENTS,		{GL_UNSIGNED_INT, 3} },
	{ VertexArray::DataType::UNSIGNED_INT_4_COMPONENTS,		{GL_UNSIGNED_INT, 4} },

	{ VertexArray::DataType::HALF_FLOAT_1_COMPONENT,		{GL_HALF_FLOAT, 1} },
	{ VertexArray::DataType::HALF_FLOAT_2_COMPONENTS,		{GL_HALF_FLOAT, 2} },
	{ VertexArray::DataType::HALF_FLOAT_3_COMPONENTS,		{GL_HALF_FLOAT, 3} },
	{ VertexArray::DataType::HALF_FLOAT_4_COMPONENTS,		{GL_HALF_FLOAT, 4} },

	{ VertexArray::DataType::FLOAT_1_COMPONENT,				{GL_FLOAT, 1} },
	{ VertexArray::DataType::FLOAT_2_COMPONENTS,			{GL_FLOAT, 2} },
	{ VertexArray::DataType::FLOAT_3_COMPONENTS,			{GL_FLOAT, 3} },
	{ VertexArray::DataType::FLOAT_4_COMPONENTS,			{GL_FLOAT, 4} }
};

inline VertexArray::VertexArray(): m_id(0)
{
}


inline VertexArray::~VertexArray()
{
	if( m_id )
		glDeleteVertexArrays( 1, &m_id );
}


inline void VertexArray::create()
{
	if( m_id )
		return;

	glGenVertexArrays( 1, &m_id );
	assert(glGetError() == GL_NO_ERROR);
}


inline void VertexArray::setIntAttribute(unsigned int index, DataType type, unsigned int offsetBytes, unsigned int strideBytes)
{
#ifdef IMP_DEBUG

	int boundArrayId;
	glGetIntegerv( GL_VERTEX_ARRAY_BINDING, &boundTexId );
	assert( boundArrayId == m_id );
	assert( type <= VertexArray::UNSIGNED_INT_4_COMPONENTS );

#endif

	const AttributeData ad = FormatData[type];
	glVertexAttribIPointer(index, ad.components, ad.type, strideBytes, reinterpret_cast<void*>(offsetBytes));
	assert(glGetError() == GL_NO_ERROR);
}


inline void VertexArray::setFloatAttribute(unsigned int index, DataType type, unsigned int offsetBytes, unsigned int strideBytes, bool normalize)
{
#ifdef IMP_DEBUG

	int boundArrayId;
	glGetIntegerv( GL_VERTEX_ARRAY_BINDING, &boundTexId );
	assert( boundArrayId == m_id );

#endif

	const AttributeData ad = FormatData[type];
	glVertexAttribPointer(index, ad.components, ad.type, normalize, strideBytes, reinterpret_cast<void*>(offsetBytes));
	assert(glGetError() == GL_NO_ERROR);
}


inline void VertexArray::setAttributeUsage(unsigned int index, bool enable)
{
	using AttribMethod = void (*)(GLuint);
	AttribMethod method[] =
	{
		glDisableVertexAttribArray,
		glEnableVertexAttribArray
	};

	method[static_cast<unsigned int>(enable)](index);
}


inline void VertexArray::bind() const
{
	glBindVertexArray( m_id );
	assert(glGetError() == GL_NO_ERROR);
}


inline void VertexArray::unbind() const
{
	glBindVertexArray( 0 );
	assert(glGetError() == GL_NO_ERROR);
}


inline unsigned int VertexArray::getId() const
{
	return m_id;
}
