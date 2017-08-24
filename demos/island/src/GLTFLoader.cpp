#include "GLTFLoader.hpp"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "tiny_gltf.h"

// https://github.com/KhronosGroup/glTF/tree/master/specification/2.0

class MeshBuilder
{
public:

    MeshBuilder() = default;

    const MeshData& build(tinygltf::Primitive& primitive, tinygltf::Model& model);

protected:

    int getComponentSize(std::int32_t componentType) const;

private:

    MeshData m_meshData;
};


const MeshData& MeshBuilder::build(tinygltf::Primitive& primitive, tinygltf::Model& model)
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
        //"JOINTS_0", // not supported yet
        //"WEIGHTS_0" // not supported yet
    };

    std::uint32_t accessorIndex = primitive.indices;
    auto accessor = model.accessors[accessorIndex];
    auto bufferView = model.bufferViews[accessor.bufferView];
    auto buffer =  model.buffers[bufferView.buffer];

    // get index data
    m_meshData.indicesCount = accessor.count;
    int componentSize = getComponentSize(accessor.componentType);
    m_meshData.indicesData.assign(m_meshData.indicesCount * componentSize, 0);
    for(std::uint32_t i = 0 ; i < m_meshData.indicesCount ; i++)
    {
        std::size_t srcIndex = accessor.byteOffset +
                               bufferView.byteOffset +
                               i*componentSize;
        std::size_t dstIndex = i*componentSize;
        for(int j = 0 ; j < componentSize ; j++)
            m_meshData.indicesData[dstIndex+j] = buffer.data[srcIndex+j];
    }

    // check how much space is needed for attributes
    std::uint32_t vertexStructureSize = 0;
    for( const auto& supportedAttribute : Attributes )
    {
        // check if this attribute was specified
        auto attribute = primitive.attributes.find(supportedAttribute);
        if( attribute == primitive.attributes.end() )
            continue;

        // get access to attribute data
        accessorIndex = attribute->second;
        accessor = model.accessors[accessorIndex];

        m_meshData.vertexCount = accessor.count;
        vertexStructureSize += getComponentSize(accessor.componentType);
    }

    // prepare attributes data in correct order as an array of structures
    auto attributesSize = vertexStructureSize * m_meshData.vertexCount;
    auto attributeOffset = 0;
	m_meshData.attributesData.assign(attributesSize, 0);
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
        for(std::uint32_t i = 0 ; i < m_meshData.vertexCount ; i++)
        {
            std::size_t srcIndex = accessor.byteOffset +
                                   bufferView.byteOffset +
                                   bufferView.byteStride +
                                   i * componentSize;
            std::size_t dstIndex = i * vertexStructureSize + attributeOffset;
            for(int j = 0 ; j < componentSize ; j++)
                m_meshData.attributesData[dstIndex+j] = buffer.data[srcIndex+j];
        }
        attributeOffset += componentSize;
    }

    // load primitive material
    //auto material = model.materials[primitive.material];
    // ...

    return m_meshData;
}

int MeshBuilder::getComponentSize(std::int32_t componentType) const
{
    static std::map<std::int32_t, std::int32_t> componentStrides =
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

bool GLTFLoader::load(const std::string& filename, MeshDataHandler handler)
{
    tinygltf::Model model;
    tinygltf::TinyGLTF loader;
    std::string loadError;

    if (!loader.LoadASCIIFromFile(&model, &loadError, filename))
    {
        std::cout << loadError;
        return false;
    }

	MeshBuilder meshBuilder;
    for(auto& mesh : model.meshes)
    {
        for(auto& primitive : mesh.primitives)
        {
            const MeshData& meshData = meshBuilder.build(primitive, model);
			handler(meshData);
            // ... get mesh data
            // ... create mesh
        }
    }

    return true;
}
