#pragma once

#include "shadows/Data.hpp"

#include <engine/GLProgram.hpp>
#include <engine/Scene.hpp>
#include <engine/Viewport.hpp>
#include <memory>

class LightRenderer final : public engine::GLProgram
{
  private:
    GLuint m_PVMatID;
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;
    std::shared_ptr<engine::Camera> m_camera;
    engine::Viewport m_viewport;

    void createVaoVboEbo(const PlanLightData& plan);

  public:
    void render(const SceneData& sceneData, GLuint shadowTexture) const;
    LightRenderer(const engine::PipelineShaderPaths& shaderPaths, std::shared_ptr<engine::Camera> camera);
    ~LightRenderer();

    void setViewport(const engine::Viewport& viewport);
};
