#ifndef IMP_MESH_DATA
#define IMP_MESH_DATA

#include <cstdint>
#include <vector>
#include <map>
#include <array>
#include "TextureFlags.hpp"

namespace imp
{

class TextureData
{
public:

	/// Texture width
	uint32_t width;

	/// Texture height
	uint32_t height;

	/// Minification filtering type
	imp::MinFilter minFilter;

	/// Mognification filtering type
	imp::MagFilter magFilter;

	/// Wrap modes for UVs outside [0,1]
	imp::WrapMode wrapS;
	imp::WrapMode wrapT;
	imp::WrapMode wrapR;

	/// Texture data
	const unsigned char* imageData;
};

class MeshData
{

public:

	enum class Attribute
	{
		POSITION,
		NORMAL,
		TANGENT,
		TEX_COORD_0,
		TEX_COORD_1,
		TEX_COORD_2,
		TEX_COORD_3,
	};

public:

	/// Number of vertex definitions in attributes vector
	uint32_t vertexCount;

	/// Number of indices defined in indices array
	uint32_t indicesCount;

	/// Indices data type, eg. GL_UNSIGNED_INT
	int indicesType;

	/// Attributes used by this mesh
	std::vector<Attribute> attributes;

	/// Vertex attributes in form of array of structures
	/// containing all data for each vertex
	std::vector<uint8_t> attributesData;

	/// Vertex indices
	std::vector<uint8_t> indicesData;

	/// Specifies what kind of primitives to render, eg. GL_TRIANGLES
	uint32_t drawMode;

	/// Mesh bounding box
	std::array<float, 4> boundingBoxMin;
	std::array<float, 4> boundingBoxMax;

	/// Map of textures and their names
	std::map<std::string, TextureData> textures;
};

}

#endif // MESH_DATA
