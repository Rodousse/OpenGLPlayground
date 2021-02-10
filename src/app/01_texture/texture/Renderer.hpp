#pragma once

#include <engine/GLProgram.hpp>
#include <memory>
#include <stbipp/Image.hpp>

class Renderer final : public engine::GLProgram
{
  private:
    GLuint m_vao;
    GLuint m_vboPos;
    GLuint m_vboUv;
    GLuint m_ebo;

    struct Texture2D
    {
        GLuint textureID;
        GLuint textureUniID;
        int width{0};
        int height{0};
    } m_texture;
    void createVaoVboEbo();
    void setDefaultTextureData();

  public:
    void render() const;
    Renderer(const engine::PipelineShaderPaths& shaderPaths);
    ~Renderer();

    void setTexture(const stbipp::Image& image);
};
