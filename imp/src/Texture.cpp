#include "Texture.hpp"
#include <assert.h>
#include <map>

using namespace imp;

struct TexelFormatData
{
	GLint internalFormat;
	GLenum format;
	GLenum type;
};

static std::map<Texture::Format, TexelFormatData> FormatData =
{
	{ Texture::Format::RGB_8_8_8,		{GL_RGB8,	GL_RGB,		GL_UNSIGNED_BYTE} },
	{ Texture::Format::RGBA_8_8_8_8,	{GL_RGBA8,	GL_RGBA,	GL_UNSIGNED_BYTE} },
};


Texture::Texture()
	: m_id(0)
	, m_size{ 0, 0 }
{
}


Texture::~Texture()
{
	if( !m_id )
		return;

	glDeleteTextures( 1, &m_id );
	m_id = 0;
}


void Texture::create( Format pf, const Size& size, const void* data )
{
	if( ( m_size.width != size.width ) || ( m_size.height != size.height ) )
	{
		glDeleteTextures( 1, &m_id );
		glGenTextures( 1, &m_id );
	}

	m_size = size;
	m_pixelFormat = pf;

	glBindTexture( GL_TEXTURE_2D, m_id );

	const TexelFormatData fd = FormatData[m_pixelFormat];
	glTexImage2D( GL_TEXTURE_2D,
				  0,
				  fd.internalFormat,
				  m_size.width,
				  m_size.height,
				  0,
				  fd.format,
				  fd.type,
				  data );

	assert(glGetError() == GL_NO_ERROR);
}


void Texture::genMipmaps()
{

#ifdef IMP_DEBUG

	assert( glIsEnabled( GL_TEXTURE_2D ) );

	int boundTexId;
	glGetIntegerv( GL_TEXTURE_BINDING_2D, &boundTexId );
	assert( boundTexId == m_id );

#endif

	if( !m_id )
		return;

	glGenerateMipmap( GL_TEXTURE_2D );

	assert(glGetError() == GL_NO_ERROR);
}


void Texture::setMipmap( GLint level, void* data )
{
#ifdef IMP_DEBUG

	assert( glIsEnabled( GL_TEXTURE_2D ) );

	int boundTexId;
	glGetIntegerv( GL_TEXTURE_BINDING_2D, &boundTexId );
	assert( boundTexId == m_id );

#endif

	if( !data || !m_id || !level )
		return;

	GLsizei w = m_size.width >> level;
	GLsizei h = m_size.height >> level;

	// if both mipmap width and height
	// are equal 0 then level was to big
	if( !w && !h )
		return;

	if( w == 0 )
		w = 1;
	if( h == 0 )
		h = 1;

	TexelFormatData fd = FormatData[m_pixelFormat];
	glTexImage2D( GL_TEXTURE_2D,
				  level,
				  fd.internalFormat,
				  w,
				  h,
				  0,
				  fd.format,
				  fd.type,
				  data );

	assert(glGetError() == GL_NO_ERROR);
}


void Texture::createFromFrameBuffer( Format pf, const Rectangle& screenRectangle )
{
	if( !glIsEnabled( GL_TEXTURE_2D ) )
		glEnable( GL_TEXTURE_2D );

	// reuse identifier or generate new one
	if( ( m_size.width > 0 ) || ( m_size.height > 0 ) )
		glDeleteTextures( 1, &m_id );
	else
		glGenTextures( 1, &m_id );

	m_size = { screenRectangle.width, screenRectangle.height };
	m_pixelFormat = pf;

	assert(glGetError() == GL_NO_ERROR);

	const TexelFormatData fd = FormatData[m_pixelFormat];
	glBindTexture( GL_TEXTURE_2D, m_id );
	glCopyTexImage2D( GL_TEXTURE_2D,
					  0,
					  fd.internalFormat,
					  screenRectangle.llxCorner,
					  screenRectangle.llyCorner,
					  screenRectangle.width,
					  screenRectangle.height,
					  0 );
	
	assert(glGetError() == GL_NO_ERROR);
}


void Texture::replace( const Rectangle& screenRectangle, void* data )
{
	if( !glIsEnabled( GL_TEXTURE_2D ) )
		glEnable( GL_TEXTURE_2D );

	const TexelFormatData fd = FormatData[m_pixelFormat];
	glBindTexture( GL_TEXTURE_2D, m_id );
	glTexSubImage2D( GL_TEXTURE_2D,
					 0,
					 screenRectangle.llxCorner,
					 screenRectangle.llyCorner,
					 screenRectangle.width,
					 screenRectangle.height,
					 fd.format,
					 fd.type,
					 data );
					 
	// NOTE: mip maps aren't generated

	assert(glGetError() == GL_NO_ERROR);
}


bool Texture::setAnisotropicFilter( float value )
{
#ifdef IMP_DEBUG

	assert( glIsEnabled( GL_TEXTURE_2D ) );

	int boundTexId;
	glGetIntegerv( GL_TEXTURE_BINDING_2D, &boundTexId );
	assert( boundTexId == m_id );

#endif
/*
	if( value < 1.0f )
		value = 1.0f;
	else
	{
		float maxValue;
		glGetFloatv( GL_MAX_TEXTURE_MAX_ANISOTROPY, &maxValue );

		if( maxValue < value )
			value = maxValue;
	}

	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, value );

	if( glGetError() != GL_NO_ERROR )
		return 0;
*/
	return 1;
}
