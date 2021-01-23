#include "triangle/Renderer.hpp"

#include <Eigen/Dense>
#include <GL/glew.h>
#include <array>

void Renderer::createVaoVbo()
{
    std::array<Eigen::Vector3f, 3> pos{
      Eigen::Vector3f{-0.5f, -0.5f, 0.0f}, Eigen::Vector3f{0.5f, -0.5f, 0.0f}, Eigen::Vector3f{0.f, 0.5f, 0.0f}};

    std::array<Eigen::Vector3f, 3> color{
      Eigen::Vector3f{1.0f, 0.0f, 0.0f}, Eigen::Vector3f{0.0f, 1.0f, 0.0f}, Eigen::Vector3f{0.0f, 0.0f, 1.0f}};

    glGenBuffers(1, &m_vboPos);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboPos);
    glBufferData(GL_ARRAY_BUFFER, pos.size() * sizeof(Eigen::Vector3f), pos.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &m_vboColor);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboColor);
    glBufferData(GL_ARRAY_BUFFER, color.size() * sizeof(Eigen::Vector3f), color.data(), GL_STATIC_DRAW);

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    {
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, m_vboPos);
        {
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Eigen::Vector3f), nullptr);
        }
        glBindBuffer(GL_ARRAY_BUFFER, m_vboColor);
        {
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Eigen::Vector3f), nullptr);
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    glBindVertexArray(0);
}

void Renderer::render() const
{
    glUseProgram(m_program);
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    glUseProgram(0);
}

Renderer::Renderer(const engine::PipelineShaderPaths& shaderPaths): engine::GLProgram(shaderPaths)
{
    createVaoVbo();
}
