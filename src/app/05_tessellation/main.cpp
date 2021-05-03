#include "engine/Viewport.hpp"
#include "tessellation/Renderer.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>
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
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

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
    shaders.tessControlShader = std::string(SHADER_PATH) + "/tesControl.tesc";
    shaders.tessEvaluationShader = std::string(SHADER_PATH) + "/tesEval.tese";
    Renderer::MaterialMaps maps{std::string(MATERIAL_PATH) + "/Color.jpg",
                                std::string(MATERIAL_PATH) + "/Displacement.jpg",
                                std::string(MATERIAL_PATH) + "/Normal.jpg"};
    Renderer renderer(shaders, scene, maps);
    const auto start = std::chrono::steady_clock::now();

    bool drawLines{false};
    float displacementAmplitude{10.0f};
    while(!glfwWindowShouldClose(window))
    {
        // update other events like input handling
        glfwPollEvents();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        {
            engine::Viewport viewport{};
            glfwGetWindowSize(window, &viewport.width, &viewport.height);
            renderer.setViewport(viewport);

            const auto now = std::chrono::steady_clock::now();
            float diff = std::chrono::duration<float>(now - start).count();
            renderer.setDirectionnalLightDir(Vector3{std::sin(diff), 0.2f, std::cos(diff)});
        }

        renderer.render();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Parameters");
        {
            ImGui::Checkbox("GL_FILL/GL_LINE", &drawLines);
            ImGui::SliderFloat("Displacement Amplitude", &displacementAmplitude, -100, 100, "%.0f");
            renderer.setPolygonMode(drawLines ? GL_LINE : GL_FILL);
            renderer.setDisplacementAmplitude(displacementAmplitude);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                        1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);
        }
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
