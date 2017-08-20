#include "GLTFLoader.hpp"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "tiny_gltf.h"

// https://github.com/KhronosGroup/glTF/tree/master/specification/2.0

class MeshBuilder
{
public:

    MeshBuilder() = default;

    bool build(tinygltf::Primitive& primitive, tinygltf::Model& model);

protected:

    int getComponentSize(int componentType) const;

private:

    unsigned int m_indicesCount;
    unsigned int m_vertexCount;

};


bool MeshBuilder::build(tinygltf::Primitive& primitive, tinygltf::Model& model)
{
    // attributes supported by builder
    const std::string Attributes[] =
    {
        "POSITION",
        "NORMAL",
        "TEXCOORD_0",
        "TEXCOORD_1",
        "TEXCOORD_2",
        "TEXCOORD_3",
    };

    unsigned int accessorIndex = primitive.indices;
    auto accessor = model.accessors[accessorIndex];
    auto bufferView = model.bufferViews[accessor.bufferView];
    auto buffer =  model.buffers[bufferView.buffer];

    // get index data
    m_indicesCount = accessor.count;
    int componentSize = getComponentSize(accessor.componentType);
    std::vector<unsigned char> indicesData(m_indicesCount * componentSize, 0);
    for(unsigned int i = 0 ; i < m_indicesCount ; i++)
    {
        std::size_t srcIndex = accessor.byteOffset +
                               bufferView.byteOffset +
                               i*componentSize;
        std::size_t dstIndex = i*componentSize;
//        for(int j = 0 ; j < componentSize ; j++)
//            indicesData[++dstIndex] = buffer.data[++srcIndex];
    }

    // check how much space is needed for attributes
    unsigned int vertexStructureSize = 0;
    for( const auto& supportedAttribute : Attributes )
    {
        // check if this attribute was specified
        auto attribute = primitive.attributes.find(supportedAttribute);
        if( attribute == primitive.attributes.end() )
            continue;

        // get access to attribute data
        accessorIndex = attribute->second;
        accessor = model.accessors[accessorIndex];

        m_vertexCount = accessor.count;
        vertexStructureSize += getComponentSize(accessor.componentType);
    }

    // prepare attributes data in correct order as an array of structures
    auto attributesSize = vertexStructureSize * m_vertexCount;
    auto attributeOffset = 0;
    std::vector<unsigned char> attributesData(attributesSize, 0);
    for( const auto& supportedAttribute : Attributes )
    {
        // check if this attribute was specified
        auto attribute = primitive.attributes.find(supportedAttribute);
        if( attribute == primitive.attributes.end() )
            continue;

        // get access to attribute data
        accessorIndex = attribute->second;
        accessor = model.accessors[accessorIndex];
        bufferView = model.bufferViews[accessor.bufferView];
        buffer =  model.buffers[bufferView.buffer];

        componentSize = getComponentSize(accessor.componentType);
        for(unsigned int i = 0 ; i < m_vertexCount ; i++)
        {
            std::size_t srcIndex = accessor.byteOffset +
                                   bufferView.byteOffset +
                                   bufferView.byteStride +
                                   i * componentSize;
            std::size_t dstIndex = i * vertexStructureSize + attributeOffset;
//            for(int j = 0 ; j < componentSize ; j++)
//                attributesData[++dstIndex] = buffer.data[++srcIndex];
        }
        attributeOffset += componentSize;
    }

    return true;
}

int MeshBuilder::getComponentSize(int componentType) const
{
    static std::map<int, int> componentStrides =
    {
        { TINYGLTF_COMPONENT_TYPE_BYTE, sizeof(char) },
        { TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE, sizeof(unsigned char) },
        { TINYGLTF_COMPONENT_TYPE_SHORT, sizeof(short) },
        { TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT, sizeof(unsigned short) },
        { TINYGLTF_COMPONENT_TYPE_INT, sizeof(int) },
        { TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT, sizeof(unsigned int) },
        { TINYGLTF_COMPONENT_TYPE_FLOAT, sizeof(float) },
        { TINYGLTF_COMPONENT_TYPE_DOUBLE, sizeof(double) }
    };
    return componentStrides[componentType];
}

bool GLTFLoader::load(const std::string& filename)
{
    tinygltf::Model model;
    tinygltf::TinyGLTF loader;
    std::string loadError;

    if (!loader.LoadASCIIFromFile(&model, &loadError, filename))
    {
        std::cout << loadError;
        return false;
    }

    for(auto& mesh : model.meshes)
    {
        for(auto& primitive : mesh.primitives)
        {
            MeshBuilder meshBuilder;
            meshBuilder.build(primitive, model);
            // ... get mesh data
            // ... create mesh
        }
    }

    return true;
}
