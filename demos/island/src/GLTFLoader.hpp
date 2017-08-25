#ifndef GLTF_LOADER
#define GLTF_LOADER

#include "MeshData.hpp"
#include <functional>
#include <string>
#include <vector>

class GLTFLoader
{
public:

	typedef std::function<void (MeshData&)> MeshDataHandler;

public:

    GLTFLoader() = default;

    bool load(const std::string &filename, MeshDataHandler handler);
};

#endif // GLTF_LOADER
