#ifndef IMP_SHADER_PROGRAM_HPP
#define IMP_SHADER_PROGRAM_HPP

#include "Shader.hpp"
#include <string>

namespace imp
{

class ShaderProgram
{

public:

	enum class UniformType
	{
		SINGLE_VALUE,	// for samplers use only this option
		VECTOR_2,
		VECTOR_3,
		VECTOR_4,
	};

	enum class UniformMatrixType
	{
		MATRIX_4_4,
		MATRIX_3_3,
		MATRIX_3_4,
		MATRIX_4_3,
		MATRIX_2_4,		// 2 columns and 4 rows
		MATRIX_4_2,
		MATRIX_2_3,
		MATRIX_3_2,
		MATRIX_2_2
	};


public:

	/// Constructor
	ShaderProgram();

	/// Destructor
	~ShaderProgram();


	/// Creates program
	bool create();

	/// Atach shader to this program. Same shader can be
	/// attached to multiple programs
	bool attach( const Shader& shader );

	/// Detach shader from program
	bool detach( const Shader& shader );

	/// Links attached shaders
	bool link() const;


	/// Bind this program
	void bind() const;

	/// Unbind this program
	void unbind() const;


    /// Specify the value of a uniform variable consisting of float
    /// values; it also alows to specify an array of values of
    /// specified type; before calling this function program must be bound
	void setUniform( int uLoc, UniformType type, float* value, int arraySize = 1 );

    /// Specify the value of a uniform variable consisting of int
    /// values; before calling this function program must be bound
	void setUniform( int uLoc, UniformType type, int* value, int arraySize = 1 );

    /// Specify the value of a uniform matrix; before
    /// calling this function program must be bound
	void setUniformMatrix( int uLoc, UniformMatrixType type, float* value, int matricesCount = 1, bool transpose = 0 );


    /// Return an integer that represents the location of a specific
    /// uniform variable within a program; returns -1 if name
    /// does not correspond to an active uniform variable in
    /// program; before calling this function program must be bound
	int getUniformLocation( const char* variableName );

    /// Retrieve uniform variable value(s)
	void getUniform( int uLoc, float* buff );

    /// Retrieve uniform variable value(s)
	void getUniform( int uLoc, int* buff );

    /// Retrieve information about an active uniform
	void getUniformInfo( int uLoc, char* nameBuff, unsigned int buffSize, int& varSize, unsigned int& varType );


    /// Get index of uniform block
    int getUniformBlockIndex(const char* blockName) const;

    /// Get size of uniform block
    /// @param blockIndex Coresponds to value retrieved with
    /// ShaderProgram::getUniformBlockIndex
    int getUniformBlockSize(int blockIndex) const;

    /// Assign a binding point to an active uniform block defined at specified index
    /// @param blockIndex Coresponds to value retrieved with
    /// ShaderProgram::getUniformBlockIndex
    /// @param bindingPoint Coresponds to value specified with
    /// UniformBuffer::setBindingPoint
    void assignBindingPointToUniformBlock(int blockIndex, int bindingPoint);


    /// Retrieve linking log
	void getLinkingLog(std::string& result) const;

    /// Return number of atached shaders
	unsigned int getAtachedShadersCount() const;

    /// Retrieve uid's of atached shaders and returns number of retrieved uid's
	int getAtachedShaderIds( unsigned int* buff, unsigned int buffSize ) const;

    /// Return program id
	unsigned int getId() const;


private:

	// program id
	unsigned int m_id;

};

}

#endif // IMP_SHADER_PROGRAM_HPP
