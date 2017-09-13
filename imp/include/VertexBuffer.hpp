#ifndef IMP_VERTEX_BUFFER_HPP
#define IMP_VERTEX_BUFFER_HPP

#include "BufferFlags.hpp"
#include <GL/glew.h>

namespace imp
{

class VertexBuffer
{

public:

	/// Constructor
	VertexBuffer();

	/// Destructor
	~VertexBuffer();


	/// Create new data storage for currently bound buffer
	/// object (any existing data will be deleted)
	bool create( BufferType type, BufferUsageFlag usageFlag, unsigned int sizeInBytes, const void* data );


	/// Bind this buffer
	void bind() const;

	/// Unbind this buffer
	void unbind() const;


	/// Return pointer for data stored in VBO
	template<typename DataType>
	DataType* mapBuffer( BufferAccessFlag af = BufferAccessFlag::READ_WRITE );

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
	BufferType getType() const;


private:

	// handle to buffer
	unsigned int		m_id;
	
	// buffer type
	BufferType	m_bufferType;

};

#include "VertexBuffer.inl"

}

#endif // IMP_VERTEX_BUFFER_HPP
