#include "RenderBuffer.hpp"
#include <assert.h>
#include <map>

using namespace imp;



struct BufferFormatData
{
	GLenum format;
	GLbitfield clearMask;
};


static std::map<RenderBuffer::Format, BufferFormatData> FormatData =
{
	{ RenderBuffer::Format::RGB_8_8_8,				{ GL_RGB8, GL_COLOR_BUFFER_BIT } },
	{ RenderBuffer::Format::RGBA_8_8_8_8,			{ GL_RGBA8, GL_COLOR_BUFFER_BIT } },
	{ RenderBuffer::Format::DEPTH_16,				{ GL_DEPTH_COMPONENT16, GL_DEPTH_BUFFER_BIT } },
	{ RenderBuffer::Format::DEPTH_24,				{ GL_DEPTH_COMPONENT24, GL_DEPTH_BUFFER_BIT } },
	{ RenderBuffer::Format::DEPTH_32F,				{ GL_DEPTH_COMPONENT32F, GL_DEPTH_BUFFER_BIT } },
	{ RenderBuffer::Format::DEPTH_24_STENCIL_8,		{ GL_DEPTH24_STENCIL8, GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT } },
	{ RenderBuffer::Format::DEPTH_32F_STENCIL_8,	{ GL_DEPTH32F_STENCIL8, GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT } },
	{ RenderBuffer::Format::STENCIL_8,				{ GL_STENCIL_INDEX8, GL_STENCIL_BUFFER_BIT } },
};


RenderBuffer::RenderBuffer()
	: m_id(0)
	, m_width(0)
	, m_height(0)
	, m_format(Format::RGB_8_8_8)
{
}


RenderBuffer::~RenderBuffer()
{
	if( !m_id )
		return;

	glDeleteRenderbuffers( 1, &m_id );
}


void RenderBuffer::create( Format format, unsigned short width, unsigned short height )
{
	m_format = format;
	m_width = width;
	m_height = height;

	if( m_id )
		glDeleteRenderbuffers( 1, &m_id );
	glGenRenderbuffers( 1, &m_id );

	glBindRenderbuffer( GL_RENDERBUFFER, m_id );
	glRenderbufferStorage( GL_RENDERBUFFER, FormatData[m_format].format, width, height );

	assert(glGetError() == GL_NO_ERROR);
}


void RenderBuffer::clear()
{
	assert( 0 != m_id );

	glBindRenderbuffer( GL_RENDERBUFFER, m_id );
	glClear( FormatData[m_format].clearMask );
}


void RenderBuffer::bind() const
{
	assert( 0 != m_id );

	glBindRenderbuffer( GL_RENDERBUFFER, m_id );
}


void RenderBuffer::unbind() const
{
	glBindRenderbuffer( GL_RENDERBUFFER, 0 );
}


unsigned short RenderBuffer::getWidth() const
{
	return m_width;
}


unsigned short RenderBuffer::getHeight() const
{
	return m_height;
}


unsigned int RenderBuffer::getId() const
{
	return m_id;
}