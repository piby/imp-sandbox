#include <assert.h>

inline UniformBuffer::UniformBuffer(): m_id(0)
{
}


inline UniformBuffer::~UniformBuffer()
{
	if( m_id )
		glDeleteBuffers( 1, &m_id );
}


inline bool UniformBuffer<StructType>::allocate( UsageFlag usageFlag, unsigned int sizeInBytes, void *data )
{
	if( !m_id ) 
		glGenBuffers( 1, &m_id );

	if( glGetError() != GL_NO_ERROR )
		return 0;

	glBindBuffer( GL_UNIFORM_BUFFER, m_id );
	glBufferSubData( GL_UNIFORM_BUFFER, 0, sizeInBytes, data );

	if( glGetError() != GL_NO_ERROR )
		return 0;

	glBindBuffer( GL_UNIFORM_BUFFER, 0 );

	return 1;
}


inline void UniformBuffer::bind() const
{

#ifdef IMP_DEBUG

	assert( m_id );

#endif

	glBindBuffer( GL_UNIFORM_BUFFER, m_id );
}


inline void UniformBuffer::unbind() const
{
	glBindBuffer( GL_UNIFORM_BUFFER, 0 );
}


inline bool UniformBuffer::replaceData( int offsetInBytes, unsigned int sizeInBytes, void *data )
{

#ifdef IMP_DEBUG

	int boundBuffId;
	glGetIntegerv( GL_UNIFORM_BUFFER, &boundBuffId );
	assert( boundBuffId == m_id );

#endif

	glBufferSubData( GL_UNIFORM_BUFFER, offsetInBytes, sizeInBytes, data );

	if( glGetError() != GL_NO_ERROR )
		return 0;
	return 1;
}


inline unsigned int UniformBuffer::getId() const
{
	return m_id;
}
