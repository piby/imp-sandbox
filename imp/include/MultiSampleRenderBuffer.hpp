#ifndef IMP_MULTI_SAMPLE_RENDER_BUFFER_HPP
#define IMP_MULTI_SAMPLE_RENDER_BUFFER_HPP

#include <GL/glew.h>
#include "Utils.hpp"

namespace imp
{

class MultiSampleRenderBuffer
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
	MultiSampleRenderBuffer();

	/// Destructor
	~MultiSampleRenderBuffer();


	/// Create render buffer; if it was defined earlier
	/// it will be replaced; render buffer is left bound
	void create(Format format, const Size& size, GLsizei samplesCount );

	/// Clear render buffer content
	void clear();

	/// Bind render buffer
	void bind() const;

	/// Unbind render buffer
	void unbind() const;


	/// Return render buffer width and height
	const Size& getSize() const;

	/// Return opengl id of render buffer
	GLuint getId() const;


private:

	// opengl id of render buffer
	GLuint m_id;

	// render buffer width and height in pixels
	Size m_size;

	// render buffer format
	Format m_format;
};

}

#endif // IMP_MULTI_SAMPLE_RENDER_BUFFER_HPP
