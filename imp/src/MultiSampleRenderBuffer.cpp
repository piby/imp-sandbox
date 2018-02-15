#include "MultiSampleRenderBuffer.hpp"
#include <assert.h>
#include <map>

using namespace imp;



struct BufferFormatData
{
	GLenum format;
	GLbitfield clearMask;
};


static std::map<MultiSampleRenderBuffer::Format, BufferFormatData> FormatData =
{
	{ MultiSampleRenderBuffer::Format::RGB_8_8_8,				{ GL_RGB8, GL_COLOR_BUFFER_BIT } },
	{ MultiSampleRenderBuffer::Format::RGBA_8_8_8_8,			{ GL_RGBA8, GL_COLOR_BUFFER_BIT } },
	{ MultiSampleRenderBuffer::Format::DEPTH_16,				{ GL_DEPTH_COMPONENT16, GL_DEPTH_BUFFER_BIT } },
	{ MultiSampleRenderBuffer::Format::DEPTH_24,				{ GL_DEPTH_COMPONENT24, GL_DEPTH_BUFFER_BIT } },
	{ MultiSampleRenderBuffer::Format::DEPTH_32F,				{ GL_DEPTH_COMPONENT32F, GL_DEPTH_BUFFER_BIT } },
	{ MultiSampleRenderBuffer::Format::DEPTH_24_STENCIL_8,		{ GL_DEPTH24_STENCIL8, GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT } },
	{ MultiSampleRenderBuffer::Format::DEPTH_32F_STENCIL_8,		{ GL_DEPTH32F_STENCIL8, GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT } },
	{ MultiSampleRenderBuffer::Format::STENCIL_8,				{ GL_STENCIL_INDEX8, GL_STENCIL_BUFFER_BIT } },
};


MultiSampleRenderBuffer::MultiSampleRenderBuffer()
	: m_id(0)
	, m_size{0 , 0}
	, m_format(Format::RGB_8_8_8)
{
}


MultiSampleRenderBuffer::~MultiSampleRenderBuffer()
{
	if( !m_id )
		return;

	glDeleteRenderbuffers( 1, &m_id );
}


void MultiSampleRenderBuffer::create( Format format, const Size& size, GLsizei samplesCount )
{
	m_format = format;
	m_size = size;

	if( m_id )
		glDeleteRenderbuffers( 1, &m_id );
	glGenRenderbuffers( 1, &m_id );

	glBindRenderbuffer( GL_RENDERBUFFER, m_id );
	glRenderbufferStorageMultisample( GL_RENDERBUFFER, samplesCount, FormatData[m_format].format, m_size.width, m_size.height );

	assert(glGetError() == GL_NO_ERROR);
}


void MultiSampleRenderBuffer::clear()
{
	assert( 0 != m_id );

	glBindRenderbuffer( GL_RENDERBUFFER, m_id );
	glClear( FormatData[m_format].clearMask );
}


void MultiSampleRenderBuffer::bind() const
{
	assert( 0 != m_id );

	glBindRenderbuffer( GL_RENDERBUFFER, m_id );
}


void MultiSampleRenderBuffer::unbind() const
{
	glBindRenderbuffer( GL_RENDERBUFFER, 0 );
}


const Size& MultiSampleRenderBuffer::getSize() const
{
	return m_size;
}


GLuint MultiSampleRenderBuffer::getId() const
{
	return m_id;
}
