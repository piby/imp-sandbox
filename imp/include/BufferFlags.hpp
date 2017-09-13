#ifndef IMP_BUFFER_FLAGS_HPP
#define IMP_BUFFER_FLAGS_HPP

#include <GL/glew.h>

namespace imp
{

enum class BufferType
{
	VERTEX_DATA	= GL_ARRAY_BUFFER,
	INDEX_DATA	= GL_ELEMENT_ARRAY_BUFFER
};

enum class BufferUsageFlag
{
	SPECIFIED_ONCE		= GL_STATIC_DRAW,
	UPDATED_SOMETIMES	= GL_DYNAMIC_DRAW,
	UPDATED_FREQUENTLY	= GL_STREAM_DRAW
};

enum class BufferAccessFlag
{
	READ		= GL_READ_ONLY,
	WRITE		= GL_WRITE_ONLY,
	READ_WRITE	= GL_READ_WRITE
};

}

#endif // IMP_BUFFER_FLAGS_HPP
