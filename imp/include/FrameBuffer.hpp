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
	void create( unsigned int width, unsigned int height );


	/// Attach texture
	void attach( Attachment attachment, const Texture& texture );

	/// Attach render buffer
	void attach( Attachment attachment, const RenderBuffer& texture );


	/// Bind frame buffer
	void bind();

	/// Unbind frame buffer
	void unbind();


	/// Returns frame buffer width
	int getWidth();

	/// Returns frame buffer height
	int getHeight();

	/// Returns id
	unsigned int getId();

private:

	// opengl id of frame buffer
	unsigned int m_id;

	// frame buffer width in pixels
	unsigned short m_width;

	// frame buffer height in pixels
	unsigned short m_height;
};

}

#endif // IMP_FRAME_BUFFER_HPP
