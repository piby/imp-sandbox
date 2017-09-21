#include "FrameBuffer.hpp"

#define GL_GLEXT_PROTOTYPES
#include <GL/glcorearb.h>
#include <map>

using namespace imp;


static std::map<FrameBuffer::Attachment, GLenum> AttachmentData =
{
	{ FrameBuffer::Attachment::COLOR_0,	GL_COLOR_ATTACHMENT0 },
	{ FrameBuffer::Attachment::COLOR_1,	GL_COLOR_ATTACHMENT1 },
	{ FrameBuffer::Attachment::COLOR_2,	GL_COLOR_ATTACHMENT2 },
	{ FrameBuffer::Attachment::COLOR_3,	GL_COLOR_ATTACHMENT3 },
	{ FrameBuffer::Attachment::DEPTH,	GL_DEPTH_ATTACHMENT },
	{ FrameBuffer::Attachment::STENCIL,	GL_STENCIL_ATTACHMENT },
};


FrameBuffer::FrameBuffer()
	: m_id(0)
	, m_width(0)
	, m_height(0)
{
}


FrameBuffer::~FrameBuffer()
{
	if( !m_id )
		return;

	glDeleteFramebuffers( 1, &m_id );
}


void FrameBuffer::create( GLsizei width, GLsizei height )
{
	if( m_id )
		glDeleteFramebuffers( 1, &m_id );
	glGenFramebuffers( 1, &m_id );

	m_width = static_cast<uint16_t>(width);
	m_height = static_cast<uint16_t>(height);
	glBindFramebuffer( GL_FRAMEBUFFER, m_id );
}


void FrameBuffer::attach( FrameBuffer::Attachment attachment, const Texture& texture )
{
#ifdef IMP_DEBUG

	int boundFBId;
	glGetIntegerv( GL_FRAMEBUFFER_BINDING, &boundFBId );
	assert( boundFBId == m_id );

#endif

	assert( m_id );
	assert( ( texture.getWidth() == m_width) && ( texture.getHeight() == m_height ) );

	glFramebufferTexture2D( GL_FRAMEBUFFER, AttachmentData[attachment], GL_TEXTURE_2D, texture.getId(), 0 );
}


void FrameBuffer::attach( FrameBuffer::Attachment attachment, const RenderBuffer& renderBuffer )
{
#ifdef IMP_DEBUG

	int boundFBId;
	glGetIntegerv( GL_FRAMEBUFFER_BINDING, &boundFBId );
	assert( boundFBId == m_id );

#endif

	assert( m_id );
	assert( ( renderBuffer.getWidth() == m_width) && ( renderBuffer.getHeight() == m_height ) );

	glFramebufferRenderbuffer( GL_FRAMEBUFFER, AttachmentData[attachment], GL_RENDERBUFFER, renderBuffer.getId() );
}


void FrameBuffer::bind()
{
	glBindFramebuffer( GL_FRAMEBUFFER, m_id );
	glViewport( 0, 0, m_width, m_height );

	assert( glCheckFramebufferStatus( GL_FRAMEBUFFER ) == GL_FRAMEBUFFER_COMPLETE );
}


void FrameBuffer::unbind()
{
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}


GLsizei FrameBuffer::getWidth()
{
	return m_width;
}


GLsizei FrameBuffer::getHeight()
{
	return m_height;
}


GLuint FrameBuffer::getId()
{
	return m_id;
}
