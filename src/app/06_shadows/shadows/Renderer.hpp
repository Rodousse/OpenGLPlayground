#pragma once

#include "shadows/Data.hpp"

#include <engine/GLProgram.hpp>
#include <engine/Scene.hpp>
#include <engine/Viewport.hpp>
#include <memory>

class Renderer final : public engine::GLProgram
{
  private:
    GLuint m_PVMatID;
    GLuint m_vao;
    std::shared_ptr<engine::Camera> m_camera;
    engine::Viewport m_viewport;

    void createPipelineData(const SceneData& scene);

  public:
    void render(const SceneData& sceneData, GLuint shadowTexture) const;
    Renderer(const engine::PipelineShaderPaths& shaderPaths,
             std::shared_ptr<engine::Camera> camera,
             const SceneData& scene);
    ~Renderer();

    void setViewport(const engine::Viewport& viewport);
};
