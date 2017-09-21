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
	, m_width(0)
	, m_height(0)
{
}


Texture::~Texture()
{
	if( !m_id )
		return;

	if( !glIsEnabled( GL_TEXTURE_2D ) )
		glEnable( GL_TEXTURE_2D );

	glDeleteTextures( 1, &m_id );

	m_width = 0;
	m_height = 0;
}


void Texture::create( Format pf, GLsizei width, GLsizei height, const void* data )
{
	if( !glIsEnabled( GL_TEXTURE_2D ) )
		glEnable( GL_TEXTURE_2D );

	if( ( m_width != width ) || ( m_height != height ) )
		glDeleteTextures( 1, &m_id );
	glGenTextures( 1, &m_id );

	m_width  = static_cast<uint32_t>(width);
	m_height = static_cast<uint32_t>(height);
	m_pixelFormat = pf;

	glBindTexture( GL_TEXTURE_2D, m_id );

	const TexelFormatData fd = FormatData[m_pixelFormat];
	glTexImage2D( GL_TEXTURE_2D,
				  0,
				  fd.internalFormat,
				  width,
				  height,
				  0,
				  fd.format,
				  fd.type,
				  data );

	assert(glGetError() == GL_NO_ERROR);
	setFilters( MinFilter::LINEAR, MagFilter::LINEAR );
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


void Texture::setMipmap( unsigned int level, void* data )
{
#ifdef IMP_DEBUG

	assert( glIsEnabled( GL_TEXTURE_2D ) );

	int boundTexId;
	glGetIntegerv( GL_TEXTURE_BINDING_2D, &boundTexId );
	assert( boundTexId == m_id );

#endif

	if( !data || !m_id || !level )
		return;

	uint32_t w = m_width >> level;
	uint32_t h = m_height >> level;

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
				  static_cast<GLint>(level),
				  fd.internalFormat,
				  static_cast<GLsizei>(w),
				  static_cast<GLsizei>(h),
				  0,
				  fd.format,
				  fd.type,
				  data );

	assert(glGetError() == GL_NO_ERROR);
}


void Texture::createFromFrameBuffer( Format pf, unsigned short llxCorner, unsigned short llyCorner, unsigned short width, unsigned short height )
{
	if( !glIsEnabled( GL_TEXTURE_2D ) )
		glEnable( GL_TEXTURE_2D );

	// reuse identifier or generate new one
	if( ( m_width > 0 ) || ( m_height > 0 ) )
		glDeleteTextures( 1, &m_id );
	else
		glGenTextures( 1, &m_id );

	m_width  = width;
	m_height = height;
	m_pixelFormat = pf;

	assert(glGetError() == GL_NO_ERROR);

	const TexelFormatData fd = FormatData[m_pixelFormat];
	glBindTexture( GL_TEXTURE_2D, m_id );
	glCopyTexImage2D( GL_TEXTURE_2D,
					  0,
					  fd.internalFormat,
					  llxCorner,
					  llyCorner,
					  width,
					  height,
					  0 );
	
	assert(glGetError() == GL_NO_ERROR);
}


void Texture::replace( GLint llxCorner, GLint llyCorner, GLsizei width, GLsizei height, void* data )
{
	if( !glIsEnabled( GL_TEXTURE_2D ) )
		glEnable( GL_TEXTURE_2D );

	const TexelFormatData fd = FormatData[m_pixelFormat];
	glBindTexture( GL_TEXTURE_2D, m_id );
	glTexSubImage2D( GL_TEXTURE_2D,
					 0,
					 llxCorner,
					 llyCorner,
					 width,
					 height,
					 fd.format,
					 fd.type,
					 data );
					 
	// NOTE: mip maps aren't generated

	assert(glGetError() == GL_NO_ERROR);
}


void Texture::setFilters( MinFilter minf, MagFilter magf )
{

#ifdef IMP_DEBUG

	assert( glIsEnabled( GL_TEXTURE_2D ) );

	int boundTexId;
	glGetIntegerv( GL_TEXTURE_BINDING_2D, &boundTexId );
	assert( boundTexId == m_id );

#endif

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<int>(minf) );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<int>(magf) );
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


void Texture::setWrapMode( WrapMode sCoord, WrapMode tCoord, WrapMode rCoord )
{

#ifdef IMP_DEBUG

	assert( glIsEnabled( GL_TEXTURE_2D ) );

	int boundTexId;
	glGetIntegerv( GL_TEXTURE_BINDING_2D, &boundTexId );
	assert( boundTexId == m_id );

#endif

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<int>(sCoord) );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<int>(tCoord) );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, static_cast<int>(rCoord) );
}
