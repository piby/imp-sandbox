#include "Scene.hpp"
#include "Utils.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>


using namespace imp;


Scene::Scene(GLsizei windowWidth, GLsizei windowHeight)
	: m_windowWidth(windowWidth)
	, m_windowHeight(windowHeight)
	, m_orbitAngle(0.0f)
	, m_localAngle(0.0f)
{
}


bool Scene::create()
{
	std::string dataPath("data/");
	std::string shaderPath = dataPath + "shaders/";

	std::string shaderBaseName = shaderPath + "basic";
	if( !createProgram(shaderBaseName + ".vs", shaderBaseName + ".fs", m_shaderPrograms["basic"]) )
		return false;
	shaderBaseName = shaderPath + "displayFramebuffer";
	if( !createProgram(shaderBaseName + ".vs", shaderBaseName + ".fs", m_shaderPrograms["displayFramebuffer"]))
		return false;

	int textureValue = 0;
	m_shaderPrograms["basic"].bind();
	m_shaderPrograms["basic"].setUniform(0, ShaderProgram::UniformType::SINGLE_VALUE, &textureValue);
	m_shaderPrograms["displayFramebuffer"].bind();
	m_shaderPrograms["displayFramebuffer"].setUniform(0, ShaderProgram::UniformType::SINGLE_VALUE, &textureValue);

	Sampler::Data samplerData;
	m_sampler.create(samplerData);

	MeshData quadData;
	generateQuad(quadData);
	m_flyingQuad.create(quadData);
	m_fullscreenQuad.create(quadData);

	imp::Size framebufferSize{512, 512};
	m_colorTexture.create(Texture::Format::RGBA_8_8_8_8, framebufferSize, nullptr);
	m_depthRenderBuffer.create(RenderBuffer::Format::DEPTH_24, framebufferSize);
	m_frameBuffer.create(framebufferSize);
	m_frameBuffer.attach(FrameBuffer::Attachment::COLOR_0, m_colorTexture);
	m_frameBuffer.attach(FrameBuffer::Attachment::DEPTH, m_depthRenderBuffer);
	m_frameBuffer.unbind();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	return true;
}


void Scene::update(float tick)
{
	m_localAngle += tick;
	m_orbitAngle += tick / 2.0f;

	float width = static_cast<float>(m_windowWidth);
	float height = static_cast<float>(m_windowHeight);

	// TODO: check if widow size changed

	m_projMatrix = glm::perspectiveFov(45.0f, width, height, 0.1f, 300.0f);
	m_viewMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -6.0f));
}


void Scene::draw()
{
	float localAngle = glm::sin(m_localAngle) * 0.5f;

	glm::mat4 modelMatrix = glm::rotate(glm::mat4(1.0f), m_orbitAngle, glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, -3.0f));
	modelMatrix = glm::rotate(modelMatrix, localAngle, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 mvp = m_projMatrix * m_viewMatrix * modelMatrix;

	int projMatLoc = m_shaderPrograms["displayFramebuffer"].getUniformLocation("mvpMat");
	m_shaderPrograms["displayFramebuffer"].bind();
	m_shaderPrograms["displayFramebuffer"].setUniformMatrix(projMatLoc, ShaderProgram::UniformMatrixType::MATRIX_4_4, glm::value_ptr(mvp));

	glClearColor(0.0f, 0.1f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, m_windowWidth, m_windowHeight);

	m_flyingQuad.draw();
}

bool Scene::createProgram(std::string vs, std::string fs, imp::ShaderProgram& resultProgram)
{
	std::string vertSource;
	std::string fragSource;
	imp::Shader vertShader;
	imp::Shader fragShader;

	vertSource = loadShader(vs);
	if(vertShader.create(imp::Shader::Type::VERTEX_SHADER, vertSource) < 0)
	{
		std::string log;
		vertShader.getCompilationLog(log);
		std::cout << vs << "\n" << vertSource << "\n" << log;
		return false;
	}

	fragSource = loadShader(fs);
	if(fragShader.create(imp::Shader::Type::FRAGMENT_SHADER, fragSource) < 0)
	{
		std::string log;
		fragShader.getCompilationLog(log);
		std::cout << fs << "\n" << fragSource << "\n" << log;
		return false;
	}

	resultProgram.create();
	resultProgram.attach(vertShader);
	resultProgram.attach(fragShader);
	if( !resultProgram.link() )
	{
		std::string log;
		resultProgram.getLinkingLog(log);
		std::cout << vs << "\n" << vertSource << "\n" << fs << "\n" << fragSource << "\n" << log;
		return false;
	}

	return true;
}

