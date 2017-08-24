#ifndef STATIC_MESH
#define STATIC_MESH

#include <string>
#include <vector>

#include "VertexBuffer.hpp"
#include "VertexArray.hpp"


class StaticMesh
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

    struct Data
    {
        /// Number of vertex definitions in attributes vector
        std::uint32_t verexCount;

        /// Number of indices defined in indices array
        std::uint32_t indicesCount;

        /// Components used in attributes
        std::vector<Components> components;

        /// Vertex attributes in form of array of structures
        std::vector<std::uint8_t> attributes;

        /// Vertex indices
        std::vector<std::uint8_t> indices;
    };

public:

    /// Construct
    StaticMesh();

    /// Upload mesh data to GPU
    void create( const Data& data );

    /// Draw mesh
    void draw();

protected:

    std::uint32_t m_indicesCount;

    imp::VertexBuffer m_indicesVBO;
    imp::VertexBuffer m_attributesVBO;

    imp::VertexArray m_vao;
};

#endif // SIMPLE_MESH
