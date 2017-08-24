#ifndef GLTF_LOADER
#define GLTF_LOADER

#include <functional>
#include <string>
#include <vector>

struct MeshData
{
	std::uint32_t vertexCount;
	std::uint32_t indicesCount;
	std::vector<std::uint8_t> indicesData;
	std::vector<std::uint8_t> attributesData;
};

class GLTFLoader
{
public:

	typedef std::function<void (const MeshData&)> MeshDataHandler;

public:

    GLTFLoader() = default;

    bool load(const std::string &filename, MeshDataHandler handler);
};

#endif // GLTF_LOADER
