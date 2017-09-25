#ifndef IMP_TEXTURE_FLAGS_HPP
#define IMP_TEXTURE_FLAGS_HPP

#include <GL/glew.h>

namespace imp
{

enum class MagFilter
{
	// nearest texture elements
	NEAREST	= GL_NEAREST,

	// average of the four texture elements
	LINEAR	= GL_LINEAR
};

enum class MinFilter
{
	// nearest texture elements
	NEAREST					= GL_NEAREST,

	// average of the four texture elements
	LINEAR					= GL_LINEAR,

	// choose the mipmap that most closely matches the size of
	// the pixel being textured and uses the GL_NEAREST
	NEAREST_MIPMAP_NEAREST	= GL_NEAREST_MIPMAP_NEAREST,

	// choose the mipmap that most closely matches the size of
	// the pixel being textured and uses the GL_LINEAR
	LINEAR_MIPMAP_NEAREST	= GL_LINEAR_MIPMAP_NEAREST,

	// choose the two mipmaps that most closely match the size of
	// the pixel being textured and uses the GL_NEAREST
	NEAREST_MIPMAP_LINEAR	= GL_NEAREST_MIPMAP_LINEAR,

	// choose the two mipmaps that most closely match the size of
	// the pixel being textured and uses the GL_LINEAR
	LINEAR_MIPMAP_LINEAR	= GL_LINEAR_MIPMAP_LINEAR
};

enum class WrapMode
{
	REPEAT			= GL_REPEAT,
	MIRRORED_REPEAT	= GL_MIRRORED_REPEAT,
	CLAMP_TO_EDGE	= GL_CLAMP_TO_EDGE,
	CLAMP_TO_BORDER	= GL_CLAMP_TO_BORDER
};

}

#endif // IMP_TEXTURE_FLAGS_HPP
