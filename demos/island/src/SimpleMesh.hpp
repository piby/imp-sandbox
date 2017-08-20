#ifndef SIMPLE_MESH
#define SIMPLE_MESH

#include <string>
#include <vector>

#include "VertexBuffer.hpp"
#include "VertexArray.hpp"


class SimpleMesh
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
        unsigned int verexCount;

        /// Number of indices defined in indices array
        unsigned int indicesCount;

        /// Components used in attributes
        std::vector<Components> components;

        /// Vertex attributes in form of array of structures
        std::vector<unsigned char> attributes;

        /// Vertex indices
        std::vector<unsigned char> indices;
    };

public:

    /// Construct
    SimpleMesh();

    /// Upload mesh data to GPU
    void create( const Data& data );

    /// Draw mesh
    void draw();

protected:

    unsigned int m_indicesCount;

    imp::VertexBuffer m_indicesVBO;
    imp::VertexBuffer m_attributesVBO;

    imp::VertexArray m_vao;
};

#endif // SIMPLE_MESH
