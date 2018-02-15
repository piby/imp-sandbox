#ifndef IMP_MULTI_SAMPLE_TEXTURE_HPP
#define IMP_MULTI_SAMPLE_TEXTURE_HPP

#include "SamplerFlags.hpp"
#include "Utils.hpp"
#include <GL/glew.h>

namespace imp
{

class MultiSampleTexture
{

public:

	/// Supported texture formats
	/// NOTE: must start from 0 because it is used as an index
	enum class Format
	{
		// 24-bit R8 G8 B8
		RGB_8_8_8,

		// 32-bit R8 G8 B8 A8
		RGBA_8_8_8_8,
		
		// NOTE: when adding another formats
		//		 modify also arrays storing 
		//		 glTexImage2D arguments
	};

public:

	/// Constructor
	MultiSampleTexture();

	/// Destructor
	~MultiSampleTexture();


	/// Create texture; if texture was defined earlier
	/// it will be replaced; texture is left bound
	void create( Format pf, const Size& size, GLsizei samplesCount, bool fixedSampleLocations );


	/// Bind texture
	void bind() const;

	/// Unbind texture
	void unbind() const;


	/// Return texture width and height
	const Size& getSize() const;

	/// Return texture pixel format
	Format getPixelFormat() const;

	/// Return opengl id of texture
	GLuint getId() const;


private:

	// opengl id of texture
	GLuint m_id;

	// texture width and height in pixels
	Size m_size;

	// pixel format
	Format m_pixelFormat;

};

#include "MultiSampleTexture.inl"

}

#endif // IMP_MULTI_SAMPLE_TEXTURE_HPP
