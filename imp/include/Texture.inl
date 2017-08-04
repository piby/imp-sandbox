#include <assert.h>


inline void Texture::bind() const
{
	assert( glIsEnabled( GL_TEXTURE_2D ) );
	assert( ( m_width > 0 ) && ( m_height > 0 ) );

	glBindTexture( GL_TEXTURE_2D, m_id );
}


inline void Texture::unbind() const
{
	glBindTexture( GL_TEXTURE_2D, 0 );
}


inline unsigned short Texture::getWidth() const
{
	return m_width;
}


inline unsigned short Texture::getHeight() const
{
	return m_height;
}


inline Texture::MinFilter Texture::getMinFilter() const
{

#ifdef IMP_DEBUG

	assert( glIsEnabled( GL_TEXTURE_2D ) );

	int boundTexId;
	glGetIntegerv( GL_TEXTURE_BINDING_2D, &boundTexId );
	assert( boundTexId == m_id );

#endif

	int minFilter = 0;
	glGetTexParameteriv( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, &minFilter );
	return ( MinFilter ) minFilter;
}


inline Texture::MagFilter Texture::getMagFilter() const
{

#ifdef IMP_DEBUG

	assert( glIsEnabled( GL_TEXTURE_2D ) );

	int boundTexId;
	glGetIntegerv( GL_TEXTURE_BINDING_2D, &boundTexId );
	assert( boundTexId == m_id );

#endif

	int magFilter = 0;
	glGetTexParameteriv( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, &magFilter );
	return ( MagFilter ) magFilter;
}


inline Texture::WrapMode Texture::getSWrapMode() const
{

#ifdef IMP_DEBUG

	assert( glIsEnabled( GL_TEXTURE_2D ) );

	int boundTexId;
	glGetIntegerv( GL_TEXTURE_BINDING_2D, &boundTexId );
	assert( boundTexId == m_id );

#endif

	int mode = 0;
	glGetTexParameteriv( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, &mode );
	return ( WrapMode ) mode;
}


inline Texture::WrapMode Texture::getTWrapMode() const
{

#ifdef IMP_DEBUG

	assert( glIsEnabled( GL_TEXTURE_2D ) );

	int boundTexId;
	glGetIntegerv( GL_TEXTURE_BINDING_2D, &boundTexId );
	assert( boundTexId == m_id );

#endif

	int mode = 0;
	glGetTexParameteriv( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, &mode );
	return ( WrapMode ) mode;
}


inline Texture::WrapMode Texture::getRWrapMode() const
{

#ifdef IMP_DEBUG

	assert( glIsEnabled( GL_TEXTURE_2D ) );

	int boundTexId;
	glGetIntegerv( GL_TEXTURE_BINDING_2D, &boundTexId );
	assert( boundTexId == m_id );

#endif

	int mode = 0;
	glGetTexParameteriv( GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, &mode );
	return ( WrapMode ) mode;
}


inline Texture::TexelFormat Texture::getPixelFormat() const
{
	return m_pixelFormat;
}


inline unsigned int Texture::getId() const
{
	return m_id;
}
