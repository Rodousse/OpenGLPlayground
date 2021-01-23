#pragma once

#include <engine/GLProgram.hpp>

class Renderer : public engine::GLProgram
{
  private:
    GLuint m_vao;
    GLuint m_vboPos;
    GLuint m_vboUv;
    GLuint m_ebo;
    void createVaoVboEbo();

  public:
    void render() const;
    Renderer(const engine::PipelineShaderPaths& shaderPaths);
    ~Renderer() final;
};
