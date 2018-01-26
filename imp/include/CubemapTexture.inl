#include <assert.h>


inline void CubemapTexture::bind() const
{
	assert( glIsEnabled( GL_TEXTURE_CUBE_MAP ) );
	assert( ( m_size.width > 0 ) && ( m_size.height > 0 ) );

	glBindTexture( GL_TEXTURE_CUBE_MAP, m_id );
}


inline void CubemapTexture::unbind() const
{
	glBindTexture( GL_TEXTURE_CUBE_MAP, 0 );
}


inline const Size& CubemapTexture::getSize() const
{
	return m_size;
}


inline CubemapTexture::Format CubemapTexture::getPixelFormat() const
{
	return m_pixelFormat;
}


inline GLuint CubemapTexture::getId() const
{
	return m_id;
}
