#include "GLTFLoader.hpp"
#include "TextureFlags.hpp"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "tiny_gltf.h"

// https://github.com/KhronosGroup/glTF/tree/master/specification/2.0

using namespace imp;

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
    //{ MeshData::Components::JOINTS_0,   "JOINTS_0" }, // not supported yet
    //{ MeshData::Components::WEIGHTS_0,  "WEIGHTS_0" }, // not supported yet
};

static std::map<int32_t, int32_t> ComponentSize
{
    { TINYGLTF_COMPONENT_TYPE_BYTE,           sizeof(int8_t) },
    { TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE,  sizeof(uint8_t) },
    { TINYGLTF_COMPONENT_TYPE_SHORT,          sizeof(int16_t) },
    { TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT, sizeof(uint16_t) },
    { TINYGLTF_COMPONENT_TYPE_INT,            sizeof(int32_t) },
    { TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT,   sizeof(uint32_t) },
    { TINYGLTF_COMPONENT_TYPE_FLOAT,          sizeof(float) },
    { TINYGLTF_COMPONENT_TYPE_DOUBLE,         sizeof(double) }
};

static std::map<int32_t, imp::MinFilter> MinFilterConverter
{
    { TINYGLTF_TEXTURE_FILTER_NEAREST,                 imp::MinFilter::NEAREST },
    { TINYGLTF_TEXTURE_FILTER_LINEAR,                  imp::MinFilter::LINEAR },
    { TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST,  imp::MinFilter::NEAREST_MIPMAP_NEAREST },
    { TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST,   imp::MinFilter::LINEAR_MIPMAP_NEAREST },
    { TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR,   imp::MinFilter::NEAREST_MIPMAP_LINEAR },
    { TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR,    imp::MinFilter::LINEAR_MIPMAP_LINEAR }
};

static std::map<int32_t, imp::MagFilter> MagFilterConverter
{
    { TINYGLTF_TEXTURE_FILTER_NEAREST,                 imp::MagFilter::NEAREST },
    { TINYGLTF_TEXTURE_FILTER_LINEAR,                  imp::MagFilter::LINEAR },
};

static std::map<int32_t, imp::WrapMode> WrapModeConverter
{
    { TINYGLTF_TEXTURE_WRAP_RPEAT,           imp::WrapMode::REPEAT },
    { TINYGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE,   imp::WrapMode::CLAMP_TO_EDGE },
    { TINYGLTF_TEXTURE_WRAP_MIRRORED_REPEAT, imp::WrapMode::MIRRORED_REPEAT }
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
    m_meshData.drawMode = static_cast<uint32_t>(primitive.mode);

    prepareIndicesData(primitive);
    prepareAttributesData(primitive);
    prepareMaterialData(primitive);

    return m_meshData;
}


void MeshBuilder::prepareIndicesData(tinygltf::Primitive& primitive)
{
    uint32_t accessorIndex = primitive.indices;
    auto accessor = m_model.accessors[accessorIndex];
    auto bufferView = m_model.bufferViews[accessor.bufferView];
    auto buffer =  m_model.buffers[bufferView.buffer];

    m_meshData.indicesCount = accessor.count;
    m_meshData.indicesType = accessor.componentType;
    int componentSize = ComponentSize[accessor.componentType];
    m_meshData.indicesData.assign(m_meshData.indicesCount * componentSize, 0);
    for(uint32_t i = 0 ; i < m_meshData.indicesCount ; i++)
    {
        size_t srcIndex = accessor.byteOffset +
                               bufferView.byteOffset +
                               i*componentSize;
        size_t dstIndex = i*componentSize;
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

    // copy bounding box dimensions
    m_meshData.boundingBoxMin = { 0.0f, 0.0f, 0.0f, 0.0f };
    m_meshData.boundingBoxMax = { 0.0f, 0.0f, 0.0f, 0.0f };

    auto positionAttribute = primitive.attributes.find("POSITION");
    assert( positionAttribute != primitive.attributes.end() );
    uint32_t accessorIndex = positionAttribute->second;
    auto accessor = m_model.accessors[accessorIndex];

    uint32_t index = 0;
    std::array<float, 4>& array = m_meshData.boundingBoxMin;
    assert( accessor.minValues.size() < 5 );
    auto copyVectorFunc = [&index, &array](double value) { array[index] = value; };
    std::for_each(accessor.minValues.begin(), accessor.minValues.end(), copyVectorFunc);
    index = 0;
    array = m_meshData.boundingBoxMax;
    std::for_each(accessor.maxValues.begin(), accessor.maxValues.end(), copyVectorFunc);

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
        for(uint32_t vertexIndex = 0 ; vertexIndex < m_meshData.vertexCount ; vertexIndex++)
        {
            size_t srcIndex = accessor.byteOffset +
                                   bufferView.byteOffset +
                                   vertexIndex * bufferView.byteStride;
            size_t dstIndex = vertexIndex * vertexStructureSize + attributeOffset;

            // copy all attribute bytes for current vertex
            memcpy(m_meshData.attributesData.data() + dstIndex,
                   buffer.data.data() + srcIndex, attributeSize);
        }
        attributeOffset += attributeSize;
    }

    /*
    // print attributes
    float* attributesData = reinterpret_cast<float*>(m_meshData.attributesData.data());
    for( uint32_t vertexIndex = 0 ; vertexIndex < m_meshData.vertexCount ; vertexIndex++ )
    {
        uint32_t vertexOffset = vertexIndex * vertexStructureSize / 4;
        uint32_t componentOffset = 0;
        for( auto acceptedAttribute : m_meshData.attributes )
        {
            // find this attribute
            auto attributeName = MeshAttributes.at(acceptedAttribute);
            auto attribute = primitive.attributes.find(attributeName);

            uint32_t accessorIndex = attribute->second;
            auto accessor = m_model.accessors[accessorIndex];

            // display all attribute components
            for( uint32_t i = 0 ; i < accessor.type ; ++i )
                std::cout << attributesData[vertexOffset + componentOffset + i] << " ";
            componentOffset += accessor.type;
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    */
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
        const auto& sampler = m_model.samplers[texture.sampler];

        assert(MinFilterConverter.find(sampler.minFilter) != MinFilterConverter.end());
        assert(MagFilterConverter.find(sampler.magFilter) != MagFilterConverter.end());
        assert(WrapModeConverter.find(sampler.wrapS) != WrapModeConverter.end());
        assert(WrapModeConverter.find(sampler.wrapT) != WrapModeConverter.end());
        //assert(WrapModeConverter.find(sampler.wrapR) != WrapModeConverter.end());

        TextureData textureData =
        {
            static_cast<uint16_t>(image.width),
            static_cast<uint16_t>(image.height),
            MinFilterConverter[sampler.minFilter],
            MagFilterConverter[sampler.magFilter],
            WrapModeConverter[sampler.wrapS],
            WrapModeConverter[sampler.wrapT],
            imp::WrapMode::REPEAT, // WrapModeConverter[sampler.wrapR],
            image.image.data()
        };

        std::string diffuse("diffuse");
        m_meshData.textures[diffuse] = textureData;
    }

    //const auto& material = m_model[primitive.material];
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
