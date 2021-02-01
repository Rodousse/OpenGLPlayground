#include "3d_model/Renderer.hpp"

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
    m_lightDirID = glGetUniformLocation(m_program, "lightDir");
    glUseProgram(0);
    THROW_IF_GL_ERROR;
}

void Renderer::render() const
{
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glUseProgram(m_program);

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
    const auto& viewport = m_camera->getViewportDimension();
    setViewport(viewport.x(), viewport.y());
    setDirectionnalLightDir(Vector3::Identity());
    glUseProgram(m_program);
    const auto normalMatID = glGetUniformLocation(m_program, "normal_mat");
    glUniformMatrix4fv(normalMatID, 1, GL_FALSE, m_camera->getView().inverse().transpose().eval().data());
    glUseProgram(0);
}

Renderer::~Renderer()
{
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
    glDeleteVertexArrays(1, &m_vao);
}

void Renderer::setViewport(int width, int height)
{
    m_camera->setViewportDimensions(width, height);
    const auto PV = m_camera->getProjection() * m_camera->getView();

    glViewport(0, 0, width, height);
    glUseProgram(m_program);
    glUniformMatrix4fv(m_PVMatID, 1, GL_FALSE, PV.eval().data());
    glUseProgram(0);
}

void Renderer::setDirectionnalLightDir(const Vector3& dir)
{
    glUseProgram(m_program);
    glUniform3fv(m_lightDirID, 1, dir.normalized().data());
    glUseProgram(0);
}