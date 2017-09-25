#ifndef IMP_SAMPLER_HPP
#define IMP_SAMPLER_HPP

#include "SamplerFlags.hpp"
#include <GL/glew.h>

namespace imp
{

class Sampler
{

public:

	struct Data
	{
		MinFilter minf = MinFilter::LINEAR;
		MagFilter magf = MagFilter::LINEAR;

		WrapMode sCoord = WrapMode::REPEAT;
		WrapMode tCoord = WrapMode::REPEAT;
		WrapMode rCoord = WrapMode::REPEAT;
	};


public:

	/// Constructor
	Sampler();

	/// Destructor
	~Sampler();


	/// Create or recreate sampler
	void create( const Data& data );


	/// Bind sampler
	void bind( GLuint unit ) const;

	/// Unbind sampler
	void unbind() const;


	/// Return min filter
	MinFilter getMinFilter() const;

	/// Return mag filter
	MagFilter getMagFilter() const;


	/// Get wrap mode for s coordinate
	WrapMode getSWrapMode() const;

	/// Get wrap mode for t coordinate
	WrapMode getTWrapMode() const;

	/// Get wrap mode for t coordinate
	WrapMode getRWrapMode() const;


	/// Return opengl id of sampler
	GLuint getId() const;


private:

	// opengl id of sampler
	GLuint m_id;

};

#include "Sampler.inl"

}

#endif // IMP_SAMPLER_HPP
