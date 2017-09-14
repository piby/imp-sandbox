#ifndef STATIC_MESH
#define STATIC_MESH

#include <string>
#include <vector>

#include "MeshData.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"


class StaticMesh
{

public:

    /// Construct
    StaticMesh();

    /// Upload mesh data to GPU
    void create( const imp::MeshData& data );

    /// Draw mesh
    void draw() const;

protected:

    std::uint32_t m_indicesCount;
    GLenum m_indicesType;
    GLenum m_drawMode;

    imp::VertexBuffer m_indicesVBO;
    imp::VertexBuffer m_attributesVBO;

    imp::VertexArray m_vao;
};

#endif // SIMPLE_MESH
