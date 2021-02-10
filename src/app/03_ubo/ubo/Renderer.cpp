#include "ubo/Renderer.hpp"

#include <Eigen/Dense>
#include <GL/glew.h>
#include <array>
#include <engine/GLErrorHandling.hpp>

void Renderer::createVaoVboEbo(const engine::Scene& scene)
{
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 scene.meshes[0]->vertices.size() * sizeof(scene.meshes[0]->vertices[0]),
                 scene.meshes[0]->vertices.data(),
                 GL_STATIC_DRAW);

    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 scene.meshes[0]->faces.size() * sizeof(scene.meshes[0]->faces[0]),
                 scene.meshes[0]->faces.data(),
                 GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        {
            // position
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(engine::Vertex), nullptr);
            // normals
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(
              1, 3, GL_FLOAT, GL_FALSE, sizeof(engine::Vertex), (void*)offsetof(engine::Vertex, normal));
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    }
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glUseProgram(m_program);
    m_PVMatID = glGetUniformLocation(m_program, "PV_mat");
    m_VIMatID = glGetUniformLocation(m_program, "VI_mat");
    glUseProgram(0);

    THROW_IF_GL_ERROR;
}

void Renderer::createUbo()
{
    glGenBuffers(1, &m_ubo);

    const auto blockIndex = glGetUniformBlockIndex(m_program, "UBOData");
    glUniformBlockBinding(m_program, blockIndex, 0);

    glUseProgram(m_program);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_ubo);
    glUseProgram(0);
    THROW_IF_GL_ERROR;
}

void Renderer::render() const
{
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glUseProgram(m_program);

    glUseProgram(m_program);
    glUniformMatrix4fv(m_VIMatID, 1, GL_FALSE, m_camera->getView().inverse().eval().data());
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_nbTriangles, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

    glUseProgram(0);
    glDisable(GL_CULL_FACE);
    THROW_IF_GL_ERROR;
}

Renderer::Renderer(const engine::PipelineShaderPaths& shaderPaths, const engine::Scene& scene):
  engine::GLProgram(shaderPaths), m_camera(scene.cameras[0]), m_nbTriangles(scene.meshes[0]->faces.size() * 3)
{
    createVaoVboEbo(scene);
    createUbo();
    setLightMaterial(LightMaterial{});
    const auto& viewport = m_camera->getViewportDimension();
    setViewport(viewport.x(), viewport.y());
}

Renderer::~Renderer()
{
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
    glDeleteBuffers(1, &m_ubo);
    glDeleteVertexArrays(1, &m_vao);
}

void Renderer::setViewport(int width, int height)
{
    m_camera->setViewportDimensions(width, height);
    const auto PVMat = m_camera->getProjection() * m_camera->getView();
    glUseProgram(m_program);
    glUniformMatrix4fv(m_PVMatID, 1, GL_FALSE, PVMat.eval().data());
    glUseProgram(0);
    glViewport(0, 0, width, height);
}

void Renderer::setLightMaterial(const Renderer::LightMaterial& lightMat)
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(LightMaterial), &lightMat, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    THROW_IF_GL_ERROR;
}