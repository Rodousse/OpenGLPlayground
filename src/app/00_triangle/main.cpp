#include "triangle/Renderer.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <engine/DataIO.hpp>
#include <engine/GLErrorHandling.hpp>
#include <iostream>
#include <spdlog/spdlog.h>

int main(int argc, char* argv[])
{
    spdlog::set_level(spdlog::level::trace);
    if(!glfwInit())
    {
        std::cerr << "ERROR: could not start GLFW" << std::endl;
        return 1;
    }

    auto* window = glfwCreateWindow(1024, 720, "Test", nullptr, nullptr);

    if(!window)
    {
        std::cerr << "ERROR: could not open window with GLFW3" << std::endl;
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK)
    {
        std::cerr << "ERROR: could not start GLEW" << std::endl;
        return 1;
    }

    engine::PipelineShaderPaths shaders{};
    shaders.fragmentShader = std::string(SHADER_PATH) + "/fragment.fs";
    shaders.vertexShader = std::string(SHADER_PATH) + "/vertex.vs";
    Renderer renderer(shaders);

    while(!glfwWindowShouldClose(window))
    {
        // update other events like input handling
        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        renderer.render();

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}