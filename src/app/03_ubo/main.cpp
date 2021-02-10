#include "ubo/Renderer.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <engine/DataIO.hpp>
#include <engine/GLErrorHandling.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

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

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 400");

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

    Renderer::LightMaterial lightMat{};
    lightMat.lightPosition = Vector3{200.0f, 100.0f, 0.0f};
    while(!glfwWindowShouldClose(window))
    {
        // update other events like input handling
        glfwPollEvents();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        {
            int width, height;
            glfwGetWindowSize(window, &width, &height);
            renderer.setViewport(width, height);
        }

        renderer.render();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Parameters");
        {
            ImGui::ColorEdit3("Material Diffuse Color", lightMat.materialColor.data());
            ImGui::SliderFloat("Material Specularity", &lightMat.materialSpecularity, 0.0, 600, "%.0f");
            ImGui::ColorEdit3("Light Diffuse Color", lightMat.lightDiffuseColor.data());
            ImGui::ColorEdit3("Light Specular Color", lightMat.lightSpecularColor.data());
            ImGui::ColorEdit3("Light Ambient Color", lightMat.lightAmbientColor.data());
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                        1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);
        }
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        renderer.setLightMaterial(lightMat);

        glfwSwapBuffers(window);
    }
    THROW_IF_GL_ERROR;

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}