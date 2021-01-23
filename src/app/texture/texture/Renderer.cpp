#include "texture/Renderer.hpp"

#include <Eigen/Dense>
#include <GL/glew.h>
#include <array>

void Renderer::createVaoVboEbo()
{
    std::array<Eigen::Vector3f, 4> pos{Eigen::Vector3f{-0.5f, 0.5f, 0.0f},
                                       Eigen::Vector3f{-0.5f, -0.5f, 0.0f},
                                       Eigen::Vector3f{0.5f, 0.5f, 0.0f},
                                       Eigen::Vector3f{0.5f, -0.5f, 0.0f}};

    std::array<Eigen::Vector2f, 4> uv{Eigen::Vector2f{0.0f, 0.0f},
                                      Eigen::Vector2f{0.0f, 1.0f},
                                      Eigen::Vector2f{1.0f, 0.0f},
                                      Eigen::Vector2f{1.0f, 1.0f}};

    std::array<int, 6> indices{0, 1, 2, 1, 2, 3};

    glGenBuffers(1, &m_vboPos);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboPos);
    glBufferData(GL_ARRAY_BUFFER, pos.size() * sizeof(Eigen::Vector3f), pos.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &m_vboUv);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboUv);
    glBufferData(GL_ARRAY_BUFFER, uv.size() * sizeof(Eigen::Vector2f), uv.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(
      GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(decltype(indices)::value_type), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_vboPos);
        {
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Eigen::Vector3f), nullptr);
        }
        glBindBuffer(GL_ARRAY_BUFFER, m_vboUv);
        {
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Eigen::Vector2f), nullptr);
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    }
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Renderer::render() const
{
    glUseProgram(m_program);
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

    glUseProgram(0);
}

Renderer::Renderer(const engine::PipelineShaderPaths& shaderPaths): engine::GLProgram(shaderPaths)
{
    createVaoVboEbo();
}

Renderer::~Renderer()
{
    glDeleteBuffers(1, &m_vboPos);
    glDeleteBuffers(1, &m_vboUv);
    glDeleteBuffers(1, &m_ebo);
    glDeleteVertexArrays(1, &m_vao);
}
