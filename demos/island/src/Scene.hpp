#ifndef ISLAND_SCENE
#define ISLAND_SCENE

#include <vector>
#include <string>
#include <glm/matrix.hpp>
#include "Texture.hpp"
#include "ShaderProgram.hpp"
#include "StaticMesh.hpp"

class Scene
{
public:

    /// Constructor
    Scene(GLsizei windowWidth, GLsizei windowHeight);

    /// Load all data
    void create();

    /// Update all items
    void update(float tick);

    /// Render all models
    void draw();

    /// Handle kayboard and mouse input
    void handleInput( /* TODO */ );

private:

    bool createProgram(std::string vs, std::string fs, imp::ShaderProgram& resultProgram);

    void addStaticMesh(imp::MeshData& meshData);

private:

    const GLsizei m_windowWidth;
    const GLsizei m_windowHeight;

    float m_rotationAngle;
    glm::mat4 m_projMatrix;
    glm::mat4 m_viewMatrix;

    StaticMesh m_fullscreenQuad;

    std::vector<StaticMesh> m_staticMeshes;
    imp::Texture m_staticMeshTexture;

    imp::ShaderProgram m_basicProgram;
};

#endif // ISLAND_SCENE
