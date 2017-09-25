#include "CubemapTexture.hpp"
#include <assert.h>
#include <map>

using namespace imp;

struct TexelFormatData
{
	GLint internalFormat;
	GLenum format;
	GLenum type;
};

static std::map<CubemapTexture::Format, TexelFormatData> FormatData =
{
	{ CubemapTexture::Format::RGB_8_8_8,	{GL_RGB8,	GL_RGB,		GL_UNSIGNED_BYTE} },
	{ CubemapTexture::Format::RGBA_8_8_8_8,	{GL_RGBA8,	GL_RGBA,	GL_UNSIGNED_BYTE} },
};

static const GLenum CubemapTargets[] =
{
	GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
};


CubemapTexture::CubemapTexture()
	: m_id(0)
	, m_width(0)
	, m_height(0)
{
}


CubemapTexture::~CubemapTexture()
{
	if( !m_id )
		return;

	if( !glIsEnabled( GL_TEXTURE_CUBE_MAP ) )
		glEnable( GL_TEXTURE_CUBE_MAP );

	glDeleteTextures( 1, &m_id );

	m_width = 0;
	m_height = 0;
}


void CubemapTexture::create( Format pf, GLsizei width, GLsizei height, const Data& data )
{
	if( !glIsEnabled( GL_TEXTURE_CUBE_MAP ) )
		glEnable( GL_TEXTURE_CUBE_MAP );

	if( ( m_width != width ) || ( m_height != height ) )
		glDeleteTextures( 1, &m_id );
	glGenTextures( 1, &m_id );

	m_width  = width;
	m_height = height;
	m_pixelFormat = pf;

	glBindTexture( GL_TEXTURE_CUBE_MAP, m_id );

	const TexelFormatData fd = FormatData[m_pixelFormat];

	for( uint32_t index = 0 ; index < 6 ; ++index )
	{
		glTexImage2D( CubemapTargets[index],
					  0,
					  fd.internalFormat,
					  width,
					  height,
					  0,
					  fd.format,
					  fd.type,
					  data.faces[index] );
		assert(glGetError() == GL_NO_ERROR);
	}

	setFilters( MinFilter::LINEAR, MagFilter::LINEAR );
}


void CubemapTexture::genMipmaps()
{

#ifdef IMP_DEBUG

	assert( glIsEnabled( GL_TEXTURE_CUBE_MAP ) );

	int boundTexId;
	glGetIntegerv( GL_TEXTURE_BINDING_2D, &boundTexId );
	assert( boundTexId == m_id );

#endif

	if( !m_id )
		return;

	glGenerateMipmap( GL_TEXTURE_CUBE_MAP );

	assert(glGetError() == GL_NO_ERROR);
}


void CubemapTexture::setMipmap( GLint level, const Data& data )
{
#ifdef IMP_DEBUG

	assert( glIsEnabled( GL_TEXTURE_CUBE_MAP ) );

	int boundTexId;
	glGetIntegerv( GL_TEXTURE_BINDING_2D, &boundTexId );
	assert( boundTexId == m_id );

#endif

	if( !m_id || !level ||
		!data.face.positiveX || !data.face.negativeX ||
		!data.face.positiveY || !data.face.negativeY ||
		!data.face.positiveZ || !data.face.negativeZ )
		return;

	GLsizei w = m_width >> level;
	GLsizei h = m_height >> level;

	// if both mipmap width and height
	// are equal 0 then level was to big
	if( !w && !h )
		return;

	if( w == 0 )
		w = 1;
	if( h == 0 )
		h = 1;

	TexelFormatData fd = FormatData[m_pixelFormat];

	for( uint32_t index = 0 ; index < 6 ; ++index )
	{
		glTexImage2D( CubemapTargets[index],
					  level,
					  fd.internalFormat,
					  w,
					  h,
					  0,
					  fd.format,
					  fd.type,
					  data.faces[index] );

		assert(glGetError() == GL_NO_ERROR);
	}
}


void CubemapTexture::setFilters( MinFilter minf, MagFilter magf )
{

#ifdef IMP_DEBUG

	assert( glIsEnabled( GL_TEXTURE_CUBE_MAP ) );

	int boundTexId;
	glGetIntegerv( GL_TEXTURE_BINDING_2D, &boundTexId );
	assert( boundTexId == m_id );

#endif

	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, static_cast<int>(minf) );
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, static_cast<int>(magf) );
}


void CubemapTexture::setWrapMode( WrapMode sCoord, WrapMode tCoord, WrapMode rCoord )
{

#ifdef IMP_DEBUG

	assert( glIsEnabled( GL_TEXTURE_CUBE_MAP ) );

	int boundTexId;
	glGetIntegerv( GL_TEXTURE_BINDING_2D, &boundTexId );
	assert( boundTexId == m_id );

#endif

	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, static_cast<int>(sCoord) );
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, static_cast<int>(tCoord) );
	glTexParameteri( GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, static_cast<int>(rCoord) );
}
