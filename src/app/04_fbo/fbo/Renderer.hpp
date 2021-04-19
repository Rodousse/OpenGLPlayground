#pragma once

#include "fbo/GRenderer.hpp"
#include "fbo/ShadingRenderer.hpp"

#include <engine/GLProgram.hpp>
#include <engine/Scene.hpp>
#include <engine/Viewport.hpp>
#include <memory>

class Renderer
{
  public:
    Renderer(const engine::Scene& scene);
    ~Renderer();

    void render() const;

    void setViewport(const engine::Viewport& viewport);
    void setLightMaterial(const LightMaterial& lightMat);

  private:
    engine::Viewport m_viewport{};
    GBufferTextures m_gbufferTextures{
      {{0, {GL_RGB, GL_RGB16F, GL_HALF_FLOAT, GL_COLOR_ATTACHMENT0}},
       {0, {GL_RGB, GL_RGB16_SNORM, GL_SHORT, GL_COLOR_ATTACHMENT1}},
       {0, {GL_DEPTH_STENCIL, GL_DEPTH24_STENCIL8, GL_UNSIGNED_INT_24_8, GL_DEPTH_STENCIL_ATTACHMENT}}}};
    GRenderer m_rendererGBuffer;
    ShadingRenderer m_rendererShading;
};
