#include "FrameBuffer.hpp"

#define GL_GLEXT_PROTOTYPES
#include <GL/glcorearb.h>

using namespace imp;

// http://www.gamedev.net/reference/articles/article2331.asp
// http://www.codesampler.com/oglsrc/oglsrc_14.htm#ogl_frame_buffer_object

// NOTE: this class only allows to add depth buffer to fbo
// it is also possible to add stencil and colour buffers;
// also this class renders to texture - it is posible
// to render to attached color buffer

FrameBufferObject::FrameBufferObject()
{
	glGenFramebuffers( 1, &m_fboId );
}


FrameBufferObject::~FrameBufferObject()
{
}


bool FrameBufferObject::Create( unsigned int width, unsigned int height )
{
	glBindFramebuffer( GL_FRAMEBUFFER, m_fboId );

	// create render buffer that will be used as depth buffer
	glGenRenderbuffers( 1, &m_depthBufferId );
	glBindRenderbuffer( GL_RENDERBUFFER, m_depthBufferId );

	// alocate space for render buffer
	glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height );

	// attach redner buffer to currently bound frame buffer object
	glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBufferId );

	// create texture
	glGenTextures( 1, &m_textureId );
	glBindTexture( GL_TEXTURE_2D, m_textureId );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8,  width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );

	// set filters and generate mipmaps - TODO: add function parameters
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	//glGenerateMipmap( GL_TEXTURE_2D );

	// attach created texture to FBO
	glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureId, 0 );

	bool status = ( glCheckFramebufferStatus( GL_FRAMEBUFFER ) == GL_FRAMEBUFFER_COMPLETE );

	// switch back to standard buffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// if all went OK return true
	return status;
}


void FrameBufferObject::Destroy()
{
    glDeleteTextures( 1, &m_textureId );
	glDeleteFramebuffers( 1, &m_fboId );
	glDeleteRenderbuffers( 1, &m_depthBufferId );
}


void FrameBufferObject::Bind()
{
	glBindFramebuffer( GL_FRAMEBUFFER, m_fboId );
	glViewport( 0, 0, GetWidth(), GetHeight() );
}


void FrameBufferObject::Unbind()
{
	glBindFramebuffer( GL_FRAMEBUFFER, 0 );
}


int FrameBufferObject::GetWidth()
{
	int width;
	glGetRenderbufferParameteriv( GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &width );
	return width;
}


int FrameBufferObject::GetHeight()
{
	int height;
	glGetRenderbufferParameteriv( GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &height );
	return height;
}


unsigned int FrameBufferObject::GetTextureId()
{
	return m_textureId;
}


unsigned int FrameBufferObject::GetFBOId()
{
	return m_fboId;
}
