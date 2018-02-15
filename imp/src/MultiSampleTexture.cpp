#include "MultiSampleTexture.hpp"
#include <assert.h>
#include <map>

using namespace imp;

struct TexelFormatData
{
	GLint internalFormat;
	GLenum format;
	GLenum type;
};

static std::map<MultiSampleTexture::Format, TexelFormatData> FormatData =
{
	{ MultiSampleTexture::Format::RGB_8_8_8,	{GL_RGB8,	GL_RGB,		GL_UNSIGNED_BYTE} },
	{ MultiSampleTexture::Format::RGBA_8_8_8_8,	{GL_RGBA8,	GL_RGBA,	GL_UNSIGNED_BYTE} },
};


MultiSampleTexture::MultiSampleTexture()
	: m_id(0)
	, m_size{ 0, 0 }
{
}


MultiSampleTexture::~MultiSampleTexture()
{
	if( !m_id )
		return;

	glDeleteTextures( 1, &m_id );
	m_id = 0;
}


void MultiSampleTexture::create( Format pf, const Size& size, GLsizei samplesCount, bool fixedSampleLocations )
{
	if( ( m_size.width != size.width ) || ( m_size.height != size.height ) )
	{
		glDeleteTextures( 1, &m_id );
		glGenTextures( 1, &m_id );
	}

	m_size = size;
	m_pixelFormat = pf;

	glBindTexture( GL_TEXTURE_2D_MULTISAMPLE, m_id );

	const TexelFormatData fd = FormatData[m_pixelFormat];
	glTexImage2DMultisample( GL_TEXTURE_2D_MULTISAMPLE,
				  samplesCount,
				  fd.internalFormat,
				  m_size.width,
				  m_size.height,
				  fixedSampleLocations );

	assert(glGetError() == GL_NO_ERROR);
}
