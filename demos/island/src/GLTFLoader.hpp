#ifndef GLTF_LOADER
#define GLTF_LOADER

#include <string>

class GLTFLoader
{
public:

    GLTFLoader() = default;

    bool load(const std::string &filename);
};

#endif // GLTF_LOADER
