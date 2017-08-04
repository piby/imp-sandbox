#include "ShaderProgram.hpp"
#include <gl/glew.h>
#include <windows.h>
#include <gl/gl.h>


inline void ShaderProgram::Bind() const
{
	glUseProgram( m_id );
}


inline void ShaderProgram::Unbind() const
{
	glUseProgram( 0 ); 
}
