#ifndef IMP_CUBEMAP_TEXTURE_HPP
#define IMP_CUBEMAP_TEXTURE_HPP

#include "SamplerFlags.hpp"
#include "Utils.hpp"
#include <GL/glew.h>

namespace imp
{

class CubemapTexture
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

	union Data
	{
		const void *faces[6];
		struct
		{
			const void *positiveX;
			const void *negativeX;
			const void *positiveY;
			const void *negativeY;
			const void *positiveZ;
			const void *negativeZ;
		} face;
	};

public:

	/// Constructor
	CubemapTexture();

	/// Destructor
	~CubemapTexture();


	/// Create cubemap texture; if texture was defined earlier
	/// it will be replaced; texture is left bound
	void create(Format pf, const Size& size, const Data& data );

	/// Generate mipmaps
	void genMipmaps();

	/// Set mipmap at given level (level must be greater then 0);
	/// At level 1 data should point to texels of two times smaller texture;
	/// Texture must be bound
	void setMipmap( GLint level, const Data& data );


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

#include "CubemapTexture.inl"

}

#endif // IMP_CUBEMAP_TEXTURE_HPP
