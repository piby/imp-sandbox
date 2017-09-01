#ifndef MESH_DATA
#define MESH_DATA

#include <cstdint>
#include <vector>
#include <map>

class TextureData
{
public:

    std::uint32_t width;
    std::uint32_t height;
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
    std::uint32_t vertexCount;

    /// Number of indices defined in indices array
    std::uint32_t indicesCount;

    /// Indices data type, eg. GL_UNSIGNED_INT
    int indicesType;

    /// Attributes used in mesh
    std::vector<Attribute> attributes;

    /// Vertex attributes in form of array of structures
    std::vector<std::uint8_t> attributesData;

    /// Vertex indices
    std::vector<std::uint8_t> indicesData;

    /// Specifies what kind of primitives to render, eg. GL_TRIANGLES
    std::uint32_t drawMode;

    /// Map of textures and their names
    std::map<std::string, TextureData> textures;
};

#endif // MESH_DATA
