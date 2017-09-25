#ifndef IMP_CUBEMAP_TEXTURE_HPP
#define IMP_CUBEMAP_TEXTURE_HPP

#include "SamplerFlags.hpp"
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
	void create(Format pf, GLsizei width, GLsizei height, const Data& data );

	/// Generate mipmaps
	void genMipmaps();

	/// Set mipmap at given level (level must be greater then 0);
	/// At level 1 data should point to texels of two times smaller texture;
	/// Texture must be bound
	void setMipmap( GLint level, const Data& data );

	/// Set min and mag filters; min filter is used when pixel color is calculated
	/// basing on more then one texel, mag filter is used when color is calculated
	/// basing on one texel; texture must be bound
	void setFilters( MinFilter minf, MagFilter magf );

	/// Set the wrap parameters for texture coordinates
	void setWrapMode( WrapMode sCoord, WrapMode tCoord, WrapMode rCoord );


	/// Bind texture
	void bind() const;

	/// Unbind texture
	void unbind() const;


	/// Return texture width
	GLsizei getWidth() const;

	/// Return texture height
	GLsizei getHeight() const;


	/// Return texture min filter
	MinFilter getMinFilter() const;

	/// Return texture mag filter
	MagFilter getMagFilter() const;


	/// Get wrap mode for texture s coordinate
	WrapMode getSWrapMode() const;

	/// Get wrap mode for texture t coordinate
	WrapMode getTWrapMode() const;

	/// Get wrap mode for texture r coordinate
	WrapMode getRWrapMode() const;

	
	/// Return texture pixel format
	Format getPixelFormat() const;

	/// Return opengl id of texture
	GLuint getId() const;


private:

	// opengl id of texture
	GLuint m_id;

	// texture width in pixels
	GLsizei m_width;

	// texture height in pixels
	GLsizei m_height;

	// pixel format
	Format m_pixelFormat;

};

#include "CubemapTexture.inl"

}

#endif // IMP_CUBEMAP_TEXTURE_HPP
