#include "shadows/Renderer.hpp"

#include "shadows/Data.hpp"

#include <Eigen/Dense>
#include <GL/glew.h>
#include <array>
#include <engine/CommonTypes.hpp>
#include <engine/GLErrorHandling.hpp>
#include <engine/GLTexture.hpp>
#include <memory>
#include <stbipp/Color.hpp>
#include <stbipp/Image.hpp>
#include <stbipp/ImageFormat.hpp>
#include <stbipp/ImageImporter.hpp>

void Renderer::createPipelineData(const SceneData& scene)
{
    glUseProgram(m_program);
    m_PVMatID = glGetUniformLocation(m_program, "PV_mat");
    glUseProgram(0);
    THROW_IF_GL_ERROR;
}

void Renderer::render(const SceneData& sceneData, GLuint shadowTexture) const
{
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glEnable(GL_DEPTH_TEST);
    glUseProgram(m_program);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, shadowTexture);
    glBindVertexArray(sceneData.vao());
    glDrawElements(GL_TRIANGLES, sceneData.nbFaces(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

    glUseProgram(0);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    THROW_IF_GL_ERROR;
}

Renderer::Renderer(const engine::PipelineShaderPaths& shaderPaths,
                   std::shared_ptr<engine::Camera> camera,
                   const SceneData& scene):
  engine::GLProgram(shaderPaths), m_camera(std::move(camera))
{
    createPipelineData(scene);
    const auto& viewport = m_camera->getViewportDimension();
    setViewport({0, 0, viewport.x(), viewport.y()});
}

Renderer::~Renderer() {}

void Renderer::setViewport(const engine::Viewport& viewport)
{
    if(m_viewport.width == viewport.width && m_viewport.height == viewport.height)
    {
        return;
    }
    m_viewport = viewport;
    m_camera->setViewportDimensions(viewport.width, viewport.height);
    const auto PV = m_camera->getProjection() * m_camera->getView();

    glViewport(0, 0, viewport.width, viewport.height);
    glUseProgram(m_program);
    glUniformMatrix4fv(m_PVMatID, 1, GL_FALSE, PV.eval().data());
    glUseProgram(0);
}

