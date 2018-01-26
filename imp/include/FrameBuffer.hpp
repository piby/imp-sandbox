#ifndef IMP_FRAME_BUFFER_HPP
#define IMP_FRAME_BUFFER_HPP

#include "Texture.hpp"
#include "RenderBuffer.hpp"

namespace imp
{

class FrameBuffer
{

public:

	/// Supported attachments
	enum class Attachment
	{
		COLOR_0,
		COLOR_1,
		COLOR_2,
		COLOR_3,
		DEPTH,
		STENCIL
	};

public:

	/// Constructor
	FrameBuffer();

	/// Destructor
	~FrameBuffer();


	/// Create frame buffer; if frame buffer was defined earlier
	/// it will be replaced; frame buffer is left bound
	void create( const Size& size );


	/// Attach texture
	void attach( Attachment attachment, const Texture& texture );

	/// Attach render buffer
	void attach( Attachment attachment, const RenderBuffer& texture );


	/// Bind frame buffer
	void bind();

	/// Unbind frame buffer
	void unbind();


	/// Returns frame buffer width and height
	const Size& getSize();

	/// Returns id
	GLuint getId();

private:

	// opengl id of frame buffer
	GLuint m_id;

	// frame buffer width and height in pixels
	Size m_size;
};

}

#endif // IMP_FRAME_BUFFER_HPP
