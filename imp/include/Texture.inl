#include <assert.h>


inline void Texture::bind() const
{
	assert( glIsEnabled( GL_TEXTURE_2D ) );
	assert( ( m_size.width > 0 ) && ( m_size.height > 0 ) );

	glBindTexture( GL_TEXTURE_2D, m_id );
}


inline void Texture::unbind() const
{
	glBindTexture( GL_TEXTURE_2D, 0 );
}


inline const Size& Texture::getSize() const
{
	return m_size;
}


inline Texture::Format Texture::getPixelFormat() const
{
	return m_pixelFormat;
}


inline GLuint Texture::getId() const
{
	return m_id;
}
