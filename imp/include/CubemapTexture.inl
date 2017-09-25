#include <assert.h>


inline void CubemapTexture::bind() const
{
	assert( glIsEnabled( GL_TEXTURE_CUBE_MAP ) );
	assert( ( m_width > 0 ) && ( m_height > 0 ) );

	glBindTexture( GL_TEXTURE_CUBE_MAP, m_id );
}


inline void CubemapTexture::unbind() const
{
	glBindTexture( GL_TEXTURE_CUBE_MAP, 0 );
}


inline GLsizei CubemapTexture::getWidth() const
{
	return m_width;
}


inline GLsizei CubemapTexture::getHeight() const
{
	return m_height;
}


inline MinFilter CubemapTexture::getMinFilter() const
{

#ifdef IMP_DEBUG

	assert( glIsEnabled( GL_TEXTURE_CUBE_MAP ) );

	int boundTexId;
	glGetIntegerv( GL_TEXTURE_BINDING_CUBE_MAP , &boundTexId );
	assert( boundTexId == m_id );

#endif

	int minFilter = 0;
	glGetTexParameteriv( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, &minFilter );
	return ( MinFilter ) minFilter;
}


inline MagFilter CubemapTexture::getMagFilter() const
{

#ifdef IMP_DEBUG

	assert( glIsEnabled( GL_TEXTURE_CUBE_MAP ) );

	int boundTexId;
	glGetIntegerv( GL_TEXTURE_BINDING_CUBE_MAP, &boundTexId );
	assert( boundTexId == m_id );

#endif

	int magFilter = 0;
	glGetTexParameteriv( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, &magFilter );
	return ( MagFilter ) magFilter;
}


inline WrapMode CubemapTexture::getSWrapMode() const
{

#ifdef IMP_DEBUG

	assert( glIsEnabled( GL_TEXTURE_CUBE_MAP ) );

	int boundTexId;
	glGetIntegerv( GL_TEXTURE_BINDING_CUBE_MAP, &boundTexId );
	assert( boundTexId == m_id );

#endif

	int mode = 0;
	glGetTexParameteriv( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, &mode );
	return ( WrapMode ) mode;
}


inline WrapMode CubemapTexture::getTWrapMode() const
{

#ifdef IMP_DEBUG

	assert( glIsEnabled( GL_TEXTURE_CUBE_MAP ) );

	int boundTexId;
	glGetIntegerv( GL_TEXTURE_BINDING_CUBE_MAP, &boundTexId );
	assert( boundTexId == m_id );

#endif

	int mode = 0;
	glGetTexParameteriv( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, &mode );
	return ( WrapMode ) mode;
}


inline WrapMode CubemapTexture::getRWrapMode() const
{

#ifdef IMP_DEBUG

	assert( glIsEnabled( GL_TEXTURE_CUBE_MAP ) );

	int boundTexId;
	glGetIntegerv( GL_TEXTURE_BINDING_CUBE_MAP, &boundTexId );
	assert( boundTexId == m_id );

#endif

	int mode = 0;
	glGetTexParameteriv( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, &mode );
	return ( WrapMode ) mode;
}


inline CubemapTexture::Format CubemapTexture::getPixelFormat() const
{
	return m_pixelFormat;
}


inline GLuint CubemapTexture::getId() const
{
	return m_id;
}
