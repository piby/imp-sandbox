#include "ShaderProgram.hpp"
#include <GL/glew.h>
#include <assert.h>
#include <vector>

using namespace imp;


ShaderProgram::ShaderProgram(): m_id(0)
{
}


ShaderProgram::~ShaderProgram()
{
	if( m_id )
	{
		// automatically detaches all
		// attached shaders and deletes program
		glDeleteProgram( m_id );
		m_id = 0;
	}
}


bool ShaderProgram::create()
{
	if( m_id )
		glDeleteProgram( m_id );

	// create an empty program object
	m_id = glCreateProgram();
	if( !m_id )
		return 0;
	return 1;
}


bool ShaderProgram::attach( const Shader& shader )
{
	if( ( !m_id ) || ( !shader.getId() )  )
		return 0;

	// attach shader to program object
	glAttachShader( m_id, shader.getId() );
	if( glGetError() != GL_NO_ERROR )
		return 0;
	return 1;
}	


bool ShaderProgram::detach( const Shader& shader )
{
	if( ( !m_id ) || ( !shader.getId() )  )
		return 0;

	// detach shader from program object
	glDetachShader( m_id, shader.getId() );
	if( glGetError() != GL_NO_ERROR )
		return 0;
	return 1;
}


bool ShaderProgram::link() const
{
	if( !m_id )
		return 0;

	//  links program object
	glLinkProgram( m_id );
	if( glGetError() != GL_NO_ERROR )
		return 0;

	// check if linking was successful	
	int status;
	glGetProgramiv( m_id, GL_LINK_STATUS, &status );
	if( status )
		return 1;
	return 0;
}


void ShaderProgram::bind() const
{
    glUseProgram( m_id );
}


void ShaderProgram::unbind() const
{
    glUseProgram( 0 );
}


void ShaderProgram::setUniform( int uLoc, UniformType type, float* value, int arraySize )
{
	assert( value );
	assert( arraySize > 0 );


    using UniformMethod = void (*)(GLint, GLsizei, const GLfloat*);
    UniformMethod uniformMethods[] =
    {
        glUniform1fv,
        glUniform2fv,
        glUniform3fv,
        glUniform4fv
    };

    auto index = static_cast<int>(type);
    auto method = uniformMethods[index];
    method( uLoc, arraySize, value );
}


void ShaderProgram::setUniform( int uLoc, UniformType type, int* value, int arraySize )
{
	assert( value );
	assert( arraySize > 0 );

    using UniformMethod = void (*)(GLint, GLsizei, const GLint*);
    const UniformMethod uniformMethods[] =
    {
        glUniform1iv,
        glUniform2iv,
        glUniform3iv,
        glUniform4iv
    };

    auto index = static_cast<int>(type);
    auto method = uniformMethods[index];
    method( uLoc, arraySize, value );
}


void ShaderProgram::setUniformMatrix( int uLoc, UniformMatrixType type, float* value, int matricesCount, bool transpose )
{
	assert( value );
	assert( matricesCount > 0 );

    using UniformMethod = void (*)(GLint, GLsizei, GLboolean, const GLfloat*);
    const UniformMethod uniformMethods[] =
    {
        glUniformMatrix4fv,
        glUniformMatrix3fv,
        glUniformMatrix3x4fv,
        glUniformMatrix4x3fv,
        glUniformMatrix2x4fv,
        glUniformMatrix4x2fv,
        glUniformMatrix2x3fv,
        glUniformMatrix3x2fv,
        glUniformMatrix2fv
    };

    auto index = static_cast<int>(type);
    auto method = uniformMethods[index];
    method( uLoc, matricesCount, transpose, value );
}


int ShaderProgram::getUniformLocation( const char* variableName )
{
	return glGetUniformLocation( m_id, variableName );
}

	
void ShaderProgram::getUniform( int uLoc, float* buff )
{
	glGetUniformfv( m_id, uLoc, buff );
}


void ShaderProgram::getUniform( int uLoc, int* buff )
{
	glGetUniformiv( m_id, uLoc, buff );
}


void ShaderProgram::getUniformInfo( int uLoc, char* nameBuff, unsigned int buffSize, int& varSize, unsigned int& varType )
{
	if( ( !nameBuff ) || ( !buffSize ) )
		return;

	glGetActiveUniform( m_id, uLoc, buffSize, 0, &varSize, &varType, nameBuff );
}


void ShaderProgram::getLinkingLog(std::string& result) const
{
	if( !m_id )
		return;

	int logLength = 0;
	glGetProgramiv( m_id, GL_INFO_LOG_LENGTH, &logLength );

	if( logLength > 1 )
	{
        std::vector<GLchar> log(logLength);
        glGetProgramInfoLog( m_id, logLength, 0, &log[0] );
        result = std::string(&log[0]);
	}
}


unsigned int ShaderProgram::getAtachedShadersCount() const
{
	if( !m_id )
		return 0;

	int count = 0;
	glGetProgramiv( m_id, GL_ATTACHED_SHADERS, &count );
	return count;
}

	
int ShaderProgram::getAtachedShaderIds( unsigned int* buff, unsigned int buffSize ) const
{
	if( !buffSize )
		return 0;
	
	if( !m_id )
	{
		buff[0] = 0;
		return 0;
	}

	int count = 0;
	glGetAttachedShaders( m_id, buffSize, &count, buff );

	if( ( count ) && ( (unsigned int)count > buffSize ) )
		buff[ count-1 ] = 0;
	return count;
}


unsigned int ShaderProgram::getId() const
{
	return m_id;
}

