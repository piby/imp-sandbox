#ifndef IMP_TEXTURE_HPP
#define IMP_TEXTURE_HPP

#include "SamplerFlags.hpp"
#include <GL/glew.h>

namespace imp
{

class Texture
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
	Texture();

	/// Destructor
	~Texture();


	/// Create texture; if texture was defined earlier
	/// it will be replaced; texture is left bound
	void create(Format pf, GLsizei width, GLsizei height, const void *data );

	/// Generate mipmaps
	void genMipmaps();

	/// Set mipmap at given level (level must be greater then 0);
	/// At level 1 data should point to texels of two times smaller texture;
	/// Texture must be bound
	void setMipmap( GLint level, void* data );

	/// Copy specified data from current frame buffer; If texture was defined
	/// earlier it will be replaced; Texture is left bound
	void createFromFrameBuffer( Format pf, unsigned short llxCorner, unsigned short llyCorner, unsigned short width, unsigned short height ) ;


	/// Set min and mag filters; min filter is used when pixel color is calculated
	/// basing on more then one texel, mag filter is used when color is calculated
	/// basing on one texel; texture must be bound
	void setFilters( MinFilter minf, MagFilter magf );

	/// Set anisotropic filtering; value should be equal or greater then 1.0 and
	/// smaler then max anisotropy wchih is usualy 2.0; if wallue will be out of
	/// this range it will be converted to nearest corect value; function will
	/// return 0 if this feature is unawelable or if there was an error;
	/// texture must be bound
	bool setAnisotropicFilter( float value );


	/// Set the wrap parameters for texture coordinates
	void setWrapMode( WrapMode sCoord, WrapMode tCoord );


	/// Bind texture
	void bind() const;

	/// Unbind texture
	void unbind() const;


	/// Bind texture and replace specified part of its data
	/// with different data; texture is automaticly bound
	void replace(GLint llxCorner, GLint llyCorner, GLsizei width, GLsizei height, void* data ) ;


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

#include "Texture.inl"

}

#endif // IMP_TEXTURE_HPP
