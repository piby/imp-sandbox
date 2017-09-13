#ifndef IMP_SHADER_HPP
#define IMP_SHADER_HPP

#include <GL/glew.h>
#include <string>

namespace imp
{

class Shader
{

public:

	enum class Type
	{
		VERTEX_SHADER	= GL_VERTEX_SHADER,
		FRAGMENT_SHADER	= GL_FRAGMENT_SHADER
	};


public:

	/// Constructor.
	Shader();

	/// Destructor, deletes shader or flags it for deletion
	/// until it is no longer attached to any program.
	~Shader();


	/// Creates and compiles shader, returns value
	/// less than zero in case of an error.
	int create( Type type, const std::string& sourceCode );

	/// Retrieves compilation log.
	void getCompilationLog(std::string& result) const;

	/// Returns shader type.
	Type getType() const;

	/// Returns shader id.
	unsigned int getId() const;


private:

	// shader id
	unsigned int m_id;

};

}

#endif // IMP_SHADER_HPP
