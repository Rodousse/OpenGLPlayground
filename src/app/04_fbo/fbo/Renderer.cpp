#include "fbo/Renderer.hpp"

#include <Eigen/Dense>
#include <GL/glew.h>
#include <array>
#include <engine/GLErrorHandling.hpp>
#include <engine/GLProgram.hpp>
#include <engine/GLTexture.hpp>
#include <engine/Viewport.hpp>

Renderer::Renderer(const engine::Scene& scene):
  m_rendererGBuffer{engine::PipelineShaderPaths{
                      std::string(SHADER_PATH) + "/gbuffer.vs", "", "", "", std::string(SHADER_PATH) + "/gbuffer.fs"},
                    scene},
  m_rendererShading{engine::PipelineShaderPaths{
                      std::string(SHADER_PATH) + "/shading.vs", "", "", "", std::string(SHADER_PATH) + "/shading.fs"},
                    scene}
{
}

void Renderer::render() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_rendererGBuffer.gbufferFbo());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    m_rendererGBuffer.render();
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_rendererGBuffer.gbufferFbo());
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBlitFramebuffer(m_viewport.x,
                      m_viewport.y,
                      m_viewport.width,
                      m_viewport.height,
                      m_viewport.x,
                      m_viewport.y,
                      m_viewport.width,
                      m_viewport.height,
                      GL_STENCIL_BUFFER_BIT,
                      GL_NEAREST);
    glDisable(GL_DEPTH_TEST);
    glStencilFunc(GL_EQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    m_rendererShading.render(m_gbufferTextures);
    glDisable(GL_STENCIL_TEST);
    THROW_IF_GL_ERROR;
}

void Renderer::setViewport(const engine::Viewport& viewport)
{
    if(viewport.width == m_viewport.width && viewport.height == m_viewport.height)
    {
        return;
    }
    m_viewport = viewport;

    glViewport(m_viewport.x, m_viewport.y, m_viewport.width, m_viewport.height);
    m_rendererGBuffer.refreshUniforms();

    engine::SamplerParameters sampleParams{};
    sampleParams.minFilter = GL_LINEAR;
    for(auto& gbufferAttachment: m_gbufferTextures)
    {
        auto& texture = gbufferAttachment.first;
        const auto& attachmentProperty = gbufferAttachment.second;
        if(texture != 0)
        {
            glDeleteTextures(1, &texture);
        }
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        {
            glTexImage2D(GL_TEXTURE_2D,
                         0,
                         attachmentProperty.internalFormat,
                         viewport.width,
                         viewport.height,
                         0,
                         attachmentProperty.format,
                         attachmentProperty.type,
                         0);
            if(!CHECK_NO_GL_ERROR)
            {
                throw std::runtime_error("Could not create texture object");
            }
            applySamplerParametersOnTexture(GL_TEXTURE_2D, sampleParams);
            applyTextureParameters(GL_TEXTURE_2D, engine::TextureParameters{});
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    THROW_IF_GL_ERROR;
    m_rendererGBuffer.linkAttachmentTexturesToFbo(m_gbufferTextures);
}

void Renderer::setLightMaterial(const LightMaterial& lightMat)
{
    m_rendererShading.setLightMaterial(lightMat);
}

Renderer::~Renderer()
{
    for(auto& gbufferAttachment: m_gbufferTextures)
    {
        if(gbufferAttachment.first != 0)
        {
            glDeleteTextures(1, &gbufferAttachment.first);
        }
    }
}
