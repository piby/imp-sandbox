#include "Scene.hpp"
#include "Utils.hpp"
#include "GLTFLoader.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>


using namespace imp;


Scene::Scene(GLsizei windowWidth, GLsizei windowHeight)
    : m_windowWidth(windowWidth)
    , m_windowHeight(windowHeight)
    , m_rotationAngle(0.0f)
{
}


void Scene::create()
{
    std::string dataPath("data/");
    std::string shaderPath = dataPath + "shaders/";

    createProgram(shaderPath + "basic.vs", shaderPath + "basic.fs", m_basicProgram);

    int textureValue = 0;
    m_basicProgram.bind();
    m_basicProgram.setUniform(0, ShaderProgram::UniformType::SINGLE_VALUE, &textureValue);

    MeshData fullscreenQuadData;
    generateQuad(fullscreenQuadData);
    m_fullscreenQuad.create(fullscreenQuadData);

    auto meshDataHandler = [this](MeshData& meshData) {
        this->addStaticMesh(meshData);
    };

    GLTFLoader gltfLoader;
    gltfLoader.load(dataPath + "Duck.gltf", meshDataHandler);

    float width = static_cast<float>(m_windowWidth);
    float height = static_cast<float>(m_windowHeight);
    m_projMatrix = glm::perspectiveFov(45.0f, width, height, 0.1f, 300.0f);

    glViewport(0, 0, m_windowWidth, m_windowHeight);
    glClearColor(0.1f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}


void Scene::update(float tick)
{
    m_rotationAngle += tick;
    m_viewMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, -50.0f, -250.0f));
    m_viewMatrix = glm::rotate(m_viewMatrix, m_rotationAngle, glm::vec3(0.0f, 0.9f, 0.1f));
}


void Scene::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 modelMatrix(1.0f);
    glm::mat4 mvp = m_projMatrix * m_viewMatrix * modelMatrix;

    m_basicProgram.bind();
    int projMatLoc = m_basicProgram.getUniformLocation("mvpMat");
    m_basicProgram.setUniformMatrix(projMatLoc, ShaderProgram::UniformMatrixType::MATRIX_4_4, glm::value_ptr(mvp));

    assert(glGetError() == GL_NO_ERROR);

    glActiveTexture(GL_TEXTURE0);
    m_staticMeshTexture.bind();

    for( const auto& mesh : m_staticMeshes )
        mesh.draw();

    //fullscreenQuad.draw();

    assert(glGetError() == GL_NO_ERROR);

    // render cune map:
    //   http://www.mujoco.org/book/file/desert.png
    // ...
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
        std::cout << log;
        return false;
    }

    fragSource = loadShader(fs);
    if(fragShader.create(imp::Shader::Type::FRAGMENT_SHADER, fragSource) < 0)
    {
        std::string log;
        vertShader.getCompilationLog(log);
        std::cout << log;
        return false;
    }

    resultProgram.create();
    resultProgram.attach(vertShader);
    resultProgram.attach(fragShader);
    if( !resultProgram.link() )
    {
        std::string log;
        resultProgram.getLinkingLog(log);
        std::cout << log;
        return false;
    }

    return true;
}


void Scene::addStaticMesh(imp::MeshData& meshData)
{
    m_staticMeshes.push_back(StaticMesh());
    m_staticMeshes.back().create(meshData);
    for(const auto& texture : meshData.textures)
    {
        auto& td = texture.second;
        m_staticMeshTexture.create(Texture::Format::RGB_8_8_8,
                                   static_cast<unsigned short>(td.width),
                                   static_cast<unsigned short>(td.height),
                                   td.imageData);
        m_staticMeshTexture.setWrapMode(td.wrapS, td.wrapT, td.wrapR);
        m_staticMeshTexture.setFilters(td.minFilter, td.magFilter);
        m_staticMeshTexture.genMipmaps();

        break; // TEMP: asume that there is only one model and handle only one texture for now
    }
}
