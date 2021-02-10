#include "texture/Renderer.hpp"

#include <Eigen/Dense>
#include <GL/glew.h>
#include <array>
#include <engine/GLErrorHandling.hpp>
#include <engine/GLTexture.hpp>

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

    glUseProgram(m_program);
    m_texture.textureUniID = glGetUniformLocation(m_program, "textureSampler");
    glUniform1i(m_texture.textureUniID, 0);
    glUseProgram(0);
    THROW_IF_GL_ERROR;
}

void Renderer::setDefaultTextureData()
{
    glGenTextures(1, &m_texture.textureID);
    engine::SamplerParameters sampleParams{};
    sampleParams.minFilter = GL_LINEAR;
    glBindTexture(GL_TEXTURE_2D, m_texture.textureID);
    {
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, 1, 1);
        if(!CHECK_NO_GL_ERROR)
        {
            glDeleteTextures(1, &m_texture.textureID);
            throw std::runtime_error("Could not create texture object");
        }
        applySamplerParametersOnTexture(GL_TEXTURE_2D, sampleParams);
        applyTextureParameters(GL_TEXTURE_2D, engine::TextureParameters{});
    }
}

void Renderer::render() const
{
    glUseProgram(m_program);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture.textureID);
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

    glUseProgram(0);
    THROW_IF_GL_ERROR;
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
    glDeleteTextures(1, &m_texture.textureID);
}

void Renderer::setTexture(const stbipp::Image& image)
{
    const auto textureData = image.castData<stbipp::Color4uc>();
    if(image.width() != m_texture.width || image.height() != m_texture.height)
    {
        if(m_texture.textureID != 0)
        {
            glDeleteTextures(1, &m_texture.textureID);
        }
        glGenTextures(1, &m_texture.textureID);
        glBindTexture(GL_TEXTURE_2D, m_texture.textureID);
        {
            glTexImage2D(GL_TEXTURE_2D,
                         0,
                         GL_RGB8,
                         image.width(),
                         image.height(),
                         0,
                         GL_RGBA,
                         GL_UNSIGNED_BYTE,
                         textureData.data());
            if(!CHECK_NO_GL_ERROR)
            {
                throw std::runtime_error("Could not create texture object");
            }
            engine::SamplerParameters sampleParams{};
            sampleParams.minFilter = GL_LINEAR;
            applySamplerParametersOnTexture(GL_TEXTURE_2D, sampleParams);
            applyTextureParameters(GL_TEXTURE_2D, engine::TextureParameters{});
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else if(m_texture.textureID != 0)
    {
        glBindTexture(GL_TEXTURE_2D, m_texture.textureID);
        {
            glTexSubImage2D(
              GL_TEXTURE_2D, 0, 0, 0, image.width(), image.height(), GL_RGBA, GL_UNSIGNED_BYTE, textureData.data());
            if(!CHECK_NO_GL_ERROR)
            {
                throw std::runtime_error("Could not set the data for texture object");
            }
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    THROW_IF_GL_ERROR;
}
