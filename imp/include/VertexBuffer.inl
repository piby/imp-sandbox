#include <assert.h>

inline VertexBuffer::VertexBuffer(): m_id(0)
{
}


inline VertexBuffer::~VertexBuffer()
{
	if( m_id )
		glDeleteBuffers( 1, &m_id );
}


inline bool VertexBuffer::create( VertexBuffer::Type type, VertexBuffer::UsageFlag usageFlag, unsigned int sizeInBytes, const void* data )
{
	if( !m_id ) 
		glGenBuffers( 1, &m_id );

	if( glGetError() != GL_NO_ERROR )
		return 0;

	m_bufferType = type;
	unsigned int bufferType = static_cast<unsigned int>(m_bufferType);
	glBindBuffer( bufferType, m_id );
	glBufferData( bufferType, sizeInBytes, data, static_cast<unsigned int>(usageFlag) );

	if( glGetError() != GL_NO_ERROR )
		return 0;

	glBindBuffer( bufferType, 0 );

	return 1;
}


inline void VertexBuffer::bind() const
{

#ifdef IMP_DEBUG

	assert( m_id );

#endif

	glBindBuffer( static_cast<unsigned int>(m_bufferType), m_id );
}


inline void VertexBuffer::unbind() const
{
	glBindBuffer( static_cast<unsigned int>(m_bufferType), 0 );
}


template<typename DataType>
inline DataType* VertexBuffer::mapBuffer( AccessFlag af )
{

#ifdef IMP_DEBUG

	int boundBuffId;
	glGetIntegerv( GL_ARRAY_BUFFER_BINDING, &boundBuffId );
	assert( boundBuffId == m_id );

#endif

	return static_cast<DataType*>(glMapBuffer( static_cast<unsigned int>(m_bufferType), static_cast<unsigned int>(af) ));
}


inline bool VertexBuffer::unmapBuffer() const
{

#ifdef IMP_DEBUG

	int boundBuffId;
	glGetIntegerv( GL_ARRAY_BUFFER_BINDING, &boundBuffId );
	assert( boundBuffId == m_id );

#endif

	return ( glUnmapBuffer( static_cast<unsigned int>(m_bufferType) ) == 1 );
}


inline bool VertexBuffer::replaceData( int offsetInBytes, unsigned int sizeInBytes, void *data )
{

#ifdef IMP_DEBUG

	int boundBuffId;
	glGetIntegerv( GL_ARRAY_BUFFER_BINDING, &boundBuffId );
	assert( boundBuffId == m_id );

#endif

	glBufferSubData( static_cast<unsigned int>(m_bufferType), offsetInBytes, sizeInBytes, data );

	if( glGetError() != GL_NO_ERROR )
		return 0;
	return 1;
}


inline unsigned int VertexBuffer::getSize() const
{

#ifdef IMP_DEBUG

	int boundBuffId;
	glGetIntegerv( GL_ARRAY_BUFFER_BINDING, &boundBuffId );
	assert( boundBuffId == m_id );

#endif

	int size;
	glGetBufferParameteriv( static_cast<unsigned int>(m_bufferType), GL_BUFFER_SIZE, &size );
	return size;
}


inline unsigned int VertexBuffer::getId() const
{
	return m_id;
}


inline VertexBuffer::Type VertexBuffer::getType() const
{
	return m_bufferType;
}
