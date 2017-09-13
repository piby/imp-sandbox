#ifndef IMP_TEXTURE_HPP
#define IMP_TEXTURE_HPP

#include "TextureFlags.hpp"
#include <GL/glew.h>

namespace imp
{

class Texture
{

public:

	// NOTE: must start from 0 because it is used as an index
	enum class TexelFormat
	{
		// 24-bit R8 G8 B8
		RGB_8_8_8_BYTE,

		// 24-bit R8 G8 B8
		RGB_8_8_8_UNSIGNED_BYTE,

		// 32-bit R8 G8 B8 A8
		RGBA_8_8_8_8_BYTE,

		// 32-bit R8 G8 B8 A8
		RGBA_8_8_8_8_UNSIGNED_BYTE,
		
		// NOTE: when adding another formats
		//		 modify also arrays storing 
		//		 glTexImage2D arguments
	};

public:

	// constructor
	Texture();

	// destructor
	~Texture();


	// create texture; if texture was defined earlier
	// it will be replaced; texture is left bound
	void create(TexelFormat pf, unsigned short width, unsigned short height, const void *data );

	// generate mipmaps
	void genMipmaps();

	// set mipmap at given level; level must be greater then 0;
	// at level 1 data should point to texels of texture
	// in which width and height are two times smaller;
	// texture must be bound
	void setMipmap( unsigned int level, void* data );

	// copy specified data from current frame buffer;
	// if texture was defined earlier it will be replaced;
	// texture is left bound
	void createFromFrameBuffer( TexelFormat pf, unsigned short llxCorner, unsigned short llyCorner, unsigned short width, unsigned short height ) ;


	// set min and mag filters; min filter is used 
	// when pixel color is calculated basing on more
	// then one texel, mag filter is used when color
	// is calculated basing on one texel; texture
	// must be bound
	void setFilters( MinFilter minf, MagFilter magf );

	// set anisotropic filtering; value should
	// be equal or greater then 1.0 and smaler
	// then max anisotropy wchih is usualy 2.0;
	// if wallue will be out of this range it
	// will be converted to nearest corect
	// value; function will return 0 if this
	// feature is unawelable or if there was an
	// error; texture must be bound
	bool setAnisotropicFilter( float value );


	// set the wrap parameters for texture coordinates
	void setWrapMode( WrapMode sCoord, WrapMode tCoord, WrapMode rCoord );


	// bind texture
	void bind() const;

	// unbind texture
	void unbind() const;


	// Bind texture and replace specified part of its data
	// with different data; texture is automaticly bound
	void replace( unsigned short llxCorner, unsigned short llyCorner, unsigned short width, unsigned short height, void* data ) ;


	// return texture width
	unsigned short getWidth() const;

	// return texture height
	unsigned short getHeight() const;


	// return texture min filter
	MinFilter getMinFilter() const;

	// return texture mag filter
	MagFilter getMagFilter() const;


	// get wrap mode for texture s coordinate
	WrapMode getSWrapMode() const;

	// get wrap mode for texture t coordinate
	WrapMode getTWrapMode() const;

	// get wrap mode for texture r coordinate
	WrapMode getRWrapMode() const;

	
	// return texture pixel format
	TexelFormat getPixelFormat() const;

	// return opengl id of texture
unsigned int getId() const;


private:

	// opengl id of texture
	unsigned int m_id;

	// texture width in pixels
	unsigned short m_width;

	// texture height in pixels
	unsigned short m_height;

	// pixel format
	TexelFormat m_pixelFormat;

};

#include "Texture.inl"

}

#endif // IMP_TEXTURE_HPP
