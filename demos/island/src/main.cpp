#include <string>
#include <vector>
#include <iostream>
#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "SimpleCamera.hpp"
#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "Utils.hpp"
#include "StaticMesh.hpp"
#include "GLTFLoader.hpp"

using namespace imp;
namespace chrono = std::chrono;

const int windowWidth = 800;
const int windowHeight = 600;

chrono::steady_clock::time_point lastDrawTime;

SimpleCamera simpleCamera;

VertexBuffer fullscreenQuadDataVBO;
VertexBuffer fullscreenQuadIndexVBO;
VertexArray fullscreenQuadVAO;

std::vector<StaticMesh> staticMeshes;

ShaderProgram basicProgram;

void init()
{
	GLenum error = glewInit();
	if (error != GLEW_OK)
		return;

	std::string dataPath("data/");
	std::string vertSource;
	std::string fragSource;
	imp::Shader vertShader;
	imp::Shader fragShader;

	vertSource = loadShader(dataPath + "shaders/basic.vs");
    if(vertShader.create(imp::Shader::Type::VERTEX_SHADER, vertSource) < 0)
    {
        std::string log;
        vertShader.getCompilationLog(log);
        std::cout << log;
    }

	fragSource = loadShader(dataPath + "shaders/basic.fs");
    if(fragShader.create(imp::Shader::Type::FRAGMENT_SHADER, fragSource) < 0)
    {
        std::string log;
        vertShader.getCompilationLog(log);
        std::cout << log;
    }

	basicProgram.create();
	basicProgram.attach(vertShader);
	basicProgram.attach(fragShader);
	if( !basicProgram.link() )
	{
		std::string log;
		basicProgram.getLinkingLog(log);
        std::cout << log;
	}

    fullscreenQuadDataVBO.create(
        VertexBuffer::Type::VERTEX_DATA,
        VertexBuffer::UsageFlag::SPECIFIED_ONCE,
        quadDataSize, quadData);

    fullscreenQuadIndexVBO.create(
		VertexBuffer::Type::INDEX_DATA,
		VertexBuffer::UsageFlag::SPECIFIED_ONCE,
		quadIndicesSize, quadIndices);

	unsigned int sf = sizeof(float);
	fullscreenQuadVAO.create();
	fullscreenQuadVAO.bind();

    fullscreenQuadDataVBO.bind();
    fullscreenQuadVAO.setFloatAttribute(0, VertexArray::DataType::FLOAT_3_COMPONENTS, 0, 5*sf);
    fullscreenQuadVAO.setAttributeUsage(0, true);
    fullscreenQuadVAO.setFloatAttribute(1, VertexArray::DataType::FLOAT_2_COMPONENTS, 3*sf, 5*sf);
    fullscreenQuadVAO.setAttributeUsage(1, true);
    fullscreenQuadIndexVBO.bind();

	fullscreenQuadVAO.unbind();

	auto meshDataHandler = [&staticMeshes](const MeshData& meshData) {
		//StaticMesh mesh;
		// ...
		//staticMeshes.push_back(mesh);
	};

    GLTFLoader gltfLoader;
    gltfLoader.load(dataPath + "BoxTextured.gltf", meshDataHandler);

    lastDrawTime = chrono::steady_clock::now();

	glViewport(0, 0, windowWidth, windowHeight);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void draw()
{
    chrono::steady_clock::time_point currentTime = chrono::steady_clock::now();
    chrono::duration<float> timeSpan = chrono::duration_cast<chrono::duration<float>>(currentTime - lastDrawTime);
    float tick = timeSpan.count();
    if(tick < (1.0f / 60.0f))
        return;
    lastDrawTime = currentTime;


	float width = static_cast<float>(windowWidth);
	float height = static_cast<float>(windowHeight);

	static float angle = 0.0f;
    angle += tick;
	glm::mat4 proj = glm::perspectiveFov(45.0f, width, height, 0.1f, 100.0f);
	glm::mat4 model = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -10.0f));
	model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 view = glm::mat4(1.0);


	glClear(GL_COLOR_BUFFER_BIT);

	basicProgram.bind();
	assert(glGetError() == GL_NO_ERROR);

	glm::mat4 mvp = proj * view * model;
	int projMatLoc = basicProgram.getUniformLocation("mvpMat");
	basicProgram.setUniformMatrix(projMatLoc, ShaderProgram::UniformMatrixType::MATRIX_4_4, glm::value_ptr(mvp));

	assert(glGetError() == GL_NO_ERROR);

	fullscreenQuadVAO.bind();

	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0);

	fullscreenQuadVAO.unbind();
	basicProgram.unbind();

	assert(glGetError() == GL_NO_ERROR);

	// render cune map:
	//   http://www.mujoco.org/book/file/desert.png
	// ...
}

void processInput(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	/*
	float cameraSpeed = 0.05f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	*/
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(windowWidth, windowHeight, "Island demo", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetKeyCallback(window, processInput);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	init();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
