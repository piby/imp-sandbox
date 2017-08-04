#include "Shader.hpp"
#include <vector>

using namespace imp;

Shader::Shader(): m_id(0)
{
}


Shader::~Shader()
{
	if( m_id )
	{
		glDeleteShader( m_id );
		m_id = 0;
	}
}


int Shader::create( Type type, const std::string& sourceCode )
{
	if( m_id )
		glDeleteShader( m_id );

	// create an empty shader object
    m_id = glCreateShader( static_cast<int>(type) );
	if( !m_id )
		return -1;

	// replace the source code in a shader object
    const char* source = sourceCode.c_str();
    glShaderSource( m_id, 1, &source, 0 );
	if( glGetError() != GL_NO_ERROR )
		return -2;

	// compile the source code string
	glCompileShader( m_id );	
	if( glGetError() != GL_NO_ERROR )
		return -3;

	// check if compilation was successful
	int status;
	glGetShaderiv( m_id, GL_COMPILE_STATUS, &status );
	if( status )
		return 1;
	return -4;
}


void Shader::getCompilationLog(std::string& result) const
{
    if( !m_id )
		return;

	int logLength = 0;
	glGetShaderiv( m_id, GL_INFO_LOG_LENGTH, &logLength );

	if( logLength > 1 )
	{
        std::vector<GLchar> log(logLength);
        glGetShaderInfoLog( m_id, logLength, NULL, &log[0] );
        result = std::string(&log[0]);
	}
}


Shader::Type Shader::getType() const
{
	if( !m_id )
        return Type::FRAGMENT_SHADER;

	int type;
	glGetShaderiv( m_id, GL_SHADER_TYPE, &type );
	if( type == GL_VERTEX_SHADER )
        return Type::VERTEX_SHADER;
    return Type::FRAGMENT_SHADER;
}


unsigned int Shader::getId() const
{
	return m_id;
}
