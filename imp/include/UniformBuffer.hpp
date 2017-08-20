#ifndef IMP_UNIFORM_BUFFER_HPP
#define IMP_UNIFORM_BUFFER_HPP

#include <GL/glew.h>

namespace imp
{

// Example:
//  layout (std140, binding = 2) uniform Data { float x; } myData;
//  void main() {
//    gl_Position = vec4(myData.x, 0.0, 0.0, 1.0);
//  }

class UniformBuffer
{

public:

	enum class UsageFlag
	{
		SPECIFIED_ONCE		= GL_STATIC_DRAW,
		UPDATED_SOMETIMES	= GL_DYNAMIC_DRAW,
		UPDATED_FREQUENTLY	= GL_STREAM_DRAW
	};


public:

	/// Constructor
	UniformBuffer();

	/// Destructor
	~UniformBuffer();


	/// Create new data storage for currently bound buffer
	/// object (any existing data will be deleted)
    bool create( UsageFlag usageFlag, unsigned int sizeInBytes, void *data );


	/// Bind this buffer
	void bind() const;

	/// Unbind this buffer
	void unbind() const;


	/// Replace all or part of data stored in buffer; this function is faster then maping
	bool replaceData( int offsetInBytes, unsigned int sizeInBytes, void *data );

    /// Attach the buffer to selected binding point
    /// Binding point is used by ShaderProgram to conect uniform block defined in shader
    /// with UniformBuffer object
    void setBindingPoint( unsigned int bindingPoint );

	/// Return opengl id of buffer
	unsigned int getId() const;


private:

	// handle to buffer
	unsigned int m_id;

};

#include "UniformBuffer.inl"

}

#endif // IMP_UNIFORM_BUFFER_HPP
