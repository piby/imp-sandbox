#ifndef MESH_DATA
#define MESH_DATA

#include <cstdint>
#include <vector>

class MeshData
{

public:

    enum class Components
    {
        POSITION,
        NORMAL,
        TEX_COORD_0,
        TEX_COORD_1,
        TEX_COORD_2,
        TEX_COORD_3,
    };

public:

	/// Number of vertex definitions in attributes vector
	std::uint32_t vertexCount;

	/// Number of indices defined in indices array
	std::uint32_t indicesCount;

	/// Indices data type, eg. GL_UNSIGNED_INT
	int indicesType;

	/// Components used in attributes
	std::vector<Components> components;

	/// Vertex attributes in form of array of structures
	std::vector<std::uint8_t> attributesData;

	/// Vertex indices
	std::vector<std::uint8_t> indicesData;

};

#endif // MESH_DATA
