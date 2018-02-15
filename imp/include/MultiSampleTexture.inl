#include <assert.h>


inline void MultiSampleTexture::bind() const
{
	assert( ( m_size.width > 0 ) && ( m_size.height > 0 ) );

	glBindTexture( GL_TEXTURE_2D_MULTISAMPLE, m_id );
}


inline void MultiSampleTexture::unbind() const
{
	glBindTexture( GL_TEXTURE_2D_MULTISAMPLE, 0 );
}


inline const Size& MultiSampleTexture::getSize() const
{
	return m_size;
}


inline MultiSampleTexture::Format MultiSampleTexture::getPixelFormat() const
{
	return m_pixelFormat;
}


inline GLuint MultiSampleTexture::getId() const
{
	return m_id;
}
