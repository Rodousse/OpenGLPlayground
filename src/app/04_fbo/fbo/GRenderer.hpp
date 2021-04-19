#pragma once
#include "fbo/Types.hpp"

#include <array>
#include <engine/GLProgram.hpp>
#include <engine/Scene.hpp>
#include <engine/Viewport.hpp>

class GRenderer final : public engine::GLProgram
{
  public:
    GRenderer(const engine::PipelineShaderPaths& shaderPaths, const engine::Scene& scene);
    ~GRenderer();

    void render() const;
    void refreshUniforms() const;
    GLuint gbufferFbo() const;
    void linkAttachmentTexturesToFbo(const GBufferTextures& targets) const;

  private:
    GLuint m_fbo;
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;
    GLuint m_PVMatID;
    std::shared_ptr<engine::Camera> m_camera;
    uint32_t m_indices;
    engine::Viewport m_viewport;

    void createVaoVboEbo(const engine::Scene& scene);
};
