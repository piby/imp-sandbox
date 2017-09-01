#include "GLTFLoader.hpp"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "tiny_gltf.h"

// https://github.com/KhronosGroup/glTF/tree/master/specification/2.0


// Attributes supported by builder
static const std::map<MeshData::Attribute, std::string> MeshAttributes =
{
    { MeshData::Attribute::POSITION,    "POSITION" },
    { MeshData::Attribute::NORMAL,      "NORMAL" },
	{ MeshData::Attribute::TANGENT,     "TANGENT" },
	{ MeshData::Attribute::TEX_COORD_0, "TEXCOORD_0" },
    { MeshData::Attribute::TEX_COORD_1, "TEXCOORD_1" },
    { MeshData::Attribute::TEX_COORD_2, "TEXCOORD_2" },
    { MeshData::Attribute::TEX_COORD_3, "TEXCOORD_3" },
    //{ MeshData::Components::JOINTS_0,  "JOINTS_0" }, // not supported yet
    //{ MeshData::Components::WEIGHTS_0, "WEIGHTS_0" }, // not supported yet
};

static std::map<std::int32_t, std::int32_t> ComponentSize
{
    { TINYGLTF_COMPONENT_TYPE_BYTE,           sizeof(std::int8_t) },
    { TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE,  sizeof(std::uint8_t) },
    { TINYGLTF_COMPONENT_TYPE_SHORT,          sizeof(std::int16_t) },
    { TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT, sizeof(std::uint16_t) },
    { TINYGLTF_COMPONENT_TYPE_INT,            sizeof(std::int32_t) },
    { TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT,   sizeof(std::uint32_t) },
    { TINYGLTF_COMPONENT_TYPE_FLOAT,          sizeof(float) },
    { TINYGLTF_COMPONENT_TYPE_DOUBLE,         sizeof(double) }
};


class MeshBuilder
{
public:

    MeshBuilder(tinygltf::Model& model);

    MeshData& build(tinygltf::Primitive& primitive);

protected:

    void prepareIndicesData(tinygltf::Primitive& primitive);
    void prepareAttributesData(tinygltf::Primitive& primitive);
	void prepareMaterialData(tinygltf::Primitive& primitive);

private:

    MeshData m_meshData;
    const tinygltf::Model& m_model;
};


MeshBuilder::MeshBuilder(tinygltf::Model& model)
    : m_model(model)
{
}


MeshData& MeshBuilder::build(tinygltf::Primitive& primitive)
{
    m_meshData.drawMode = primitive.mode;

    prepareIndicesData(primitive);
    prepareAttributesData(primitive);
    prepareMaterialData(primitive);

    return m_meshData;
}


void MeshBuilder::prepareIndicesData(tinygltf::Primitive& primitive)
{
    std::uint32_t accessorIndex = primitive.indices;
    auto accessor = m_model.accessors[accessorIndex];
    auto bufferView = m_model.bufferViews[accessor.bufferView];
    auto buffer =  m_model.buffers[bufferView.buffer];

    m_meshData.indicesCount = accessor.count;
    m_meshData.indicesType = accessor.componentType;
    int componentSize = ComponentSize[accessor.componentType];
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
}


void MeshBuilder::prepareAttributesData(tinygltf::Primitive& primitive)
{
    // check how much space is needed for attributes
    std::uint32_t vertexStructureSize = 0;
    for( const auto& supportedAttribute : MeshAttributes )
    {
        // check if this attribute is specified for primitive
        auto attribute = primitive.attributes.find(supportedAttribute.second);
        if( attribute == primitive.attributes.end() )
            continue;

        // get access to attribute data
        uint32_t accessorIndex = attribute->second;
        auto accessor = m_model.accessors[accessorIndex];

        // verify that attribute has 2, 3 or 4 components - matrix are not yet supported
        auto componentCount = accessor.type;
        assert( componentCount == 2 ||
                componentCount == 3 ||
                componentCount == 4 );

        // memorize vertex count
        m_meshData.vertexCount = accessor.count;

        // add this attribute to attributes vector
        m_meshData.attributes.push_back(supportedAttribute.first);

        // increase size of structure that should contain all atributes for single vertex
        vertexStructureSize += componentCount * ComponentSize[accessor.componentType];
    }

    // prepare attributes data in correct order as an array of structures
    auto allAttributesSize = vertexStructureSize * m_meshData.vertexCount;
    auto attributeOffset = 0;
    m_meshData.attributesData.assign(allAttributesSize, 0);
    for( auto acceptedAttribute : m_meshData.attributes )
    {
        // find this attribute
        auto attributeName = MeshAttributes.at(acceptedAttribute);
        auto attribute = primitive.attributes.find(attributeName);
        assert( attribute != primitive.attributes.end() );

        // get access to attribute data
        uint32_t accessorIndex = attribute->second;
        auto accessor = m_model.accessors[accessorIndex];
        auto bufferView = m_model.bufferViews[accessor.bufferView];
        auto buffer =  m_model.buffers[bufferView.buffer];

        // attribute size equels to data type size multiplyed by componentCount,
        // note that only single value, vec2, vc3 and vec4 are currently supported by loader
        auto attributeSize = ComponentSize[accessor.componentType] * accessor.type;
        for(std::uint32_t vertexIndex = 0 ; vertexIndex < m_meshData.vertexCount ; vertexIndex++)
        {
            std::size_t srcIndex = accessor.byteOffset +
                                   bufferView.byteOffset +
                                   vertexIndex * bufferView.byteStride;
            std::size_t dstIndex = vertexIndex * vertexStructureSize + attributeOffset;

            // copy all attribute bytes for current vertex
            memcpy(m_meshData.attributesData.data() + dstIndex,
                   buffer.data.data() + srcIndex, attributeSize);
        }
        attributeOffset += attributeSize;
    }
}


void MeshBuilder::prepareMaterialData(tinygltf::Primitive& primitive)
{
    //auto material = m_model.materials[primitive.material];
    // NOTE: texture index is not present in material,
    //   loading all textures which is incorrect when
    //   there is more then one model

    for(const auto& texture : m_model.textures)
    {
        const auto& image = m_model.images[texture.source];

        TextureData textureData =
        {
            image.width,
            image.height,
            image.image.data()
        };

		std::string aaa("aaa");
        m_meshData.textures[aaa] = textureData;
    }
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

    MeshBuilder meshBuilder(model);
    for(auto& mesh : model.meshes)
    {
        for(auto& primitive : mesh.primitives)
        {
            MeshData& meshData = meshBuilder.build(primitive);
            handler(meshData);
        }
    }

    return true;
}
