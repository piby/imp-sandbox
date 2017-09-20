#include <string>
#include <vector>
#include <iostream>
#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Scene.hpp"

namespace chrono = std::chrono;


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
    GLsizei windowWidth = 800;
    GLsizei windowHeight = 600;
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

    /* Initialize demo */
    chrono::steady_clock::time_point lastDrawTime;

    GLenum error = glewInit();
    if (error != GLEW_OK)
        return -1;

    Scene scene(windowWidth, windowHeight);
    scene.create();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Callculate time passed since last frame */
        chrono::steady_clock::time_point currentTime = chrono::steady_clock::now();
        chrono::duration<float> timeSpan = chrono::duration_cast<chrono::duration<float>>(currentTime - lastDrawTime);
        float tick = timeSpan.count();
        if(tick < (1.0f / 60.0f))
            continue;
        lastDrawTime = currentTime;

        /* Update and draw scene */
        scene.update(tick);
        scene.draw();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
