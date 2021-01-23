#pragma once

#include <engine/GLProgram.hpp>

class Renderer : public engine::GLProgram
{
  private:
    GLuint m_vao;
    GLuint m_vboColor;
    GLuint m_vboPos;
    void createVaoVbo();

  public:
    void render() const;
    Renderer(const engine::PipelineShaderPaths& shaderPaths);
};
