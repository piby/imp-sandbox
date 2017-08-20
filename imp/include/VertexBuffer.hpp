#ifndef IMP_VERTEX_BUFFER_HPP
#define IMP_VERTEX_BUFFER_HPP

#include <GL/glew.h>

namespace imp
{

class VertexBuffer
{

public:

	enum class Type
	{
		VERTEX_DATA	= GL_ARRAY_BUFFER,
		INDEX_DATA	= GL_ELEMENT_ARRAY_BUFFER
	};

	enum class UsageFlag
	{
		SPECIFIED_ONCE		= GL_STATIC_DRAW,
		UPDATED_SOMETIMES	= GL_DYNAMIC_DRAW,
		UPDATED_FREQUENTLY	= GL_STREAM_DRAW
	};

	enum class AccessFlag
	{
		READ		= GL_READ_ONLY,
		WRITE		= GL_WRITE_ONLY,
		READ_WRITE	= GL_READ_WRITE
	};


public:

	/// Constructor
	VertexBuffer();

	/// Destructor
	~VertexBuffer();


	/// Create new data storage for currently bound buffer
	/// object (any existing data will be deleted)
    bool create( Type type, UsageFlag usageFlag, unsigned int sizeInBytes, const void* data );


	/// Bind this buffer
	void bind() const;

	/// Unbind this buffer
	void unbind() const;


	/// Return pointer for data stored in VBO
	template<typename DataType>
	DataType* mapBuffer( AccessFlag af = AccessFlag::READ_WRITE );

	/// This function unmaps buffer data - it must be used after using
	/// MapBuffer function and before VBO data are used by application
	bool unmapBuffer() const;


	/// Replace all or part of data stored in buffer; this function is faster then maping
	bool replaceData( int offsetInBytes, unsigned int sizeInBytes, void *data );


	/// Return number of allocated bytes
	unsigned int getSize() const;

	/// Return opengl id of buffer
	unsigned int getId() const;

	/// Return target binding
	Type getType() const;


private:

	// handle to buffer
	unsigned int		m_id;
	
	// buffer type
	Type	m_bufferType;

};

#include "VertexBuffer.inl"

}

#endif // IMP_VERTEX_BUFFER_HPP
