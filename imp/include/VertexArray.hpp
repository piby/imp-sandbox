#ifndef IMP_VERTEX_ARRAY_HPP
#define IMP_VERTEX_ARRAY_HPP

#include <GL/glew.h>
#include <map>

namespace imp
{

class VertexArray
{
public:

	enum class DataType
	{
		BYTE_1_COMPONENT,
		BYTE_2_COMPONENTS,
		BYTE_3_COMPONENTS,
		BYTE_4_COMPONENTS,

		UNSIGNED_BYTE_1_COMPONENT,
		UNSIGNED_BYTE_2_COMPONENTS,
		UNSIGNED_BYTE_3_COMPONENTS,
		UNSIGNED_BYTE_4_COMPONENTS,

		SHORT_1_COMPONENT,
		SHORT_2_COMPONENTS,
		SHORT_3_COMPONENTS,
		SHORT_4_COMPONENTS,

		UNSIGNED_SHORT_1_COMPONENT,
		UNSIGNED_SHORT_2_COMPONENTS,
		UNSIGNED_SHORT_3_COMPONENTS,
		UNSIGNED_SHORT_4_COMPONENTS,

		INT_1_COMPONENT,
		INT_2_COMPONENTS,
		INT_3_COMPONENTS,
		INT_4_COMPONENTS,

		UNSIGNED_INT_1_COMPONENT,
		UNSIGNED_INT_2_COMPONENTS,
		UNSIGNED_INT_3_COMPONENTS,
		UNSIGNED_INT_4_COMPONENTS,

		HALF_FLOAT_1_COMPONENT,
		HALF_FLOAT_2_COMPONENTS,
		HALF_FLOAT_3_COMPONENTS,
		HALF_FLOAT_4_COMPONENTS,

		FLOAT_1_COMPONENT,
		FLOAT_2_COMPONENTS,
		FLOAT_3_COMPONENTS,
		FLOAT_4_COMPONENTS,

		// DOUBLE,
		// FIXED,
	};

public:

	/// Constructor
	VertexArray();

	/// Destructor
	~VertexArray();


	/// Create new vertex array
    void create();


	/// Set int attribute at specified index
	void setIntAttribute(unsigned int index, DataType type, unsigned int offsetBytes, unsigned int strideBytes);

	/// Set float attribute at specified index
	void setFloatAttribute(unsigned int index, DataType type, unsigned int offsetBytes, unsigned int strideBytes, bool normalize = false);


    /// Enable or disable attribute at specified index.
    void setAttributeUsage(unsigned int index, bool enable);


	/// Bind this array
	void bind() const;

	/// Unbind this array
	void unbind() const;


	/// Return opengl id of buffer
	unsigned int getId() const;


private:

	// handle to array
	unsigned int m_id;

};

#include "VertexArray.inl"

}

#endif // IMP_VERTEX_ARRAY_HPP
