#include "3d_model/Renderer.hpp"

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
        spdlog::critical("could not start GLFW");
        return 1;
    }

    auto* window = glfwCreateWindow(1024, 720, "Test", nullptr, nullptr);

    if(!window)
    {
        spdlog::critical("could not open window with GLFW3");
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK)
    {
        spdlog::critical("could not start GLEW");
        return 1;
    }

    engine::Scene scene{};
    if(!engine::IO::loadScene(MODEL_PATH, scene))
    {
        spdlog::critical("could not load the model file : {0}", MODEL_PATH);
    }
    scene.cameras[0]->setViewportDimensions({1024, 720});

    engine::PipelineShaderPaths shaders{};
    shaders.fragmentShader = std::string(SHADER_PATH) + "/fragment.fs";
    shaders.vertexShader = std::string(SHADER_PATH) + "/vertex.vs";
    Renderer renderer(shaders, scene);

    while(!glfwWindowShouldClose(window))
    {
        // update other events like input handling
        glfwPollEvents();

        //        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        {
            int width, height;
            glfwGetWindowSize(window, &width, &height);
            renderer.setViewport(width, height);
        }

        renderer.render();

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}