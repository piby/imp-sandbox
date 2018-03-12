#ifndef QUADS_SCENE
#define QUADS_SCENE

#include <map>
#include <vector>
#include <string>
#include <glm/matrix.hpp>
#include "Sampler.hpp"
#include "StaticMesh.hpp"
#include "FrameBuffer.hpp"
#include "ShaderProgram.hpp"

class Scene
{
public:

	/// Constructor
	Scene(GLsizei windowWidth, GLsizei windowHeight);

	/// Load all data
	bool create();

	/// Update all items
	void update(float tick);

	/// Render all models
	void draw();

	/// Handle kayboard and mouse input
	void handleInput( /* TODO */ );

private:

	bool createProgram(std::string vs, std::string fs, imp::ShaderProgram& resultProgram);

private:

	const GLsizei m_windowWidth;
	const GLsizei m_windowHeight;

	float m_orbitAngle;
	float m_localAngle;
	glm::mat4 m_projMatrix;
	glm::mat4 m_viewMatrix;

	StaticMesh m_flyingQuad;
	StaticMesh m_fullscreenQuad;

	std::vector<StaticMesh> m_staticMeshes;
	imp::Texture m_staticMeshTexture;

	std::map<std::string, imp::ShaderProgram> m_shaderPrograms;

	imp::Sampler m_sampler;
	imp::Texture m_colorTexture;
	imp::RenderBuffer m_depthRenderBuffer;
	imp::FrameBuffer m_frameBuffer;
};

#endif // ISLAND_SCENE
