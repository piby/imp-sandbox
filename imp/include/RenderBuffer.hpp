#ifndef IMP_RENDER_BUFFER_HPP
#define IMP_RENDER_BUFFER_HPP

#include <GL/glew.h>

namespace imp
{

class RenderBuffer
{

public:

	/// Supported render buffer formats
	/// NOTE: must start from 0 because it is used as an index
	enum class Format
	{
		// 24-bit R8 G8 B8
		RGB_8_8_8,

		// 32-bit R8 G8 B8 A8
		RGBA_8_8_8_8,

		// 16-bit depth
		DEPTH_16,

		// 24-bit depth
		DEPTH_24,

		// 32-bit depth
		DEPTH_32F,

		// 24-bit depth and 8-bit stencil
		DEPTH_24_STENCIL_8,

		// 32-bit depth and 8-bit stencil
		DEPTH_32F_STENCIL_8,

		// 8-bit stencil
		STENCIL_8
	};

public:

	/// Constructor
	RenderBuffer();

	/// Destructor
	~RenderBuffer();


	/// Create render buffer; if it was defined earlier
	/// it will be replaced; render buffer is left bound
	void create(Format format, unsigned short width, unsigned short height );

	/// Clear render buffer content
	void clear();

	/// Bind render buffer
	void bind() const;

	/// Unbind render buffer
	void unbind() const;


	/// Return render buffer width
	unsigned short getWidth() const;

	/// Return render buffer height
	unsigned short getHeight() const;

	/// Return opengl id of render buffer
	unsigned int getId() const;


private:

	// opengl id of render buffer
	unsigned int m_id;

	// texture width in pixels
	unsigned short m_width;

	// texture height in pixels
	unsigned short m_height;

	// render buffer format
	Format m_format;
};

}

#endif // IMP_RENDER_BUFFER_HPP
