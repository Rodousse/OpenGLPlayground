#pragma once

#include <engine/GLProgram.hpp>
#include <engine/GLTexture2D.hpp>
#include <memory>
#include <stbipp/Image.hpp>

class Renderer final : public engine::GLProgram
{
  private:
    GLuint m_vao;
    GLuint m_vboPos;
    GLuint m_vboUv;
    GLuint m_ebo;
    std::unique_ptr<engine::GLTexture2D> m_texture;
    GLuint m_textureUniID;
    void createVaoVboEbo();

  public:
    void render() const;
    Renderer(const engine::PipelineShaderPaths& shaderPaths);
    ~Renderer();

    void setTexture(const stbipp::Image& image);
};
