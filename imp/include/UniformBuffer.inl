#include <assert.h>

inline UniformBuffer::UniformBuffer(): m_id(0)
{
}


inline UniformBuffer::~UniformBuffer()
{
	if( m_id )
		glDeleteBuffers( 1, &m_id );
}


inline bool UniformBuffer::create( UniformBuffer::UsageFlag usageFlag, unsigned int sizeInBytes, void *data )
{
	if( !m_id ) 
		glGenBuffers( 1, &m_id );

	if( glGetError() != GL_NO_ERROR )
		return 0;

	glBindBuffer( GL_UNIFORM_BUFFER, m_id );
    glBufferData( GL_UNIFORM_BUFFER, sizeInBytes, data, static_cast<unsigned int>(usageFlag) );

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


void UniformBuffer::setBindingPoint( unsigned int bindingPoint )
{
#ifdef IMP_DEBUG

    assert( m_id );

#endif

    glBindBufferBase( GL_UNIFORM_BUFFER, bindingPoint, m_id );
}


inline unsigned int UniformBuffer::getId() const
{
	return m_id;
}
