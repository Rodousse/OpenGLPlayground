#pragma once

#include "fbo/Types.hpp"

#include <GL/glew.h>
#include <engine/CommonTypes.hpp>
#include <engine/GLProgram.hpp>
#include <engine/Scene.hpp>

class ShadingRenderer final : public engine::GLProgram
{
  public:
    ShadingRenderer(const engine::PipelineShaderPaths& paths, const engine::Scene& scene);
    ~ShadingRenderer();

    void render(const GBufferTextures& targets) const;
    void setLightMaterial(const LightMaterial& lightMat);

  private:
    std::array<Vector3, 4> m_vertices{
      Vector3{-1.0, 1.0, 1.0}, Vector3{-1.0, -1.0, 1.0}, Vector3{1.0, 1.0, 1.0}, Vector3{1.0, -1.0, 1.0}};
    std::array<uint32_t, 6> m_indices{0, 1, 2, 1, 3, 2};
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;
    GLuint m_ubo;
    GLuint m_camPositionID;
    std::shared_ptr<engine::Camera> m_camera;
    struct SamplerIds
    {
        GLuint position;
        GLuint normal;
    } m_samplerIDs;

    void createVaoVboEbo();
    void createUbo();
};
