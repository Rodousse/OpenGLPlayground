#pragma once

#include <engine/GLProgram.hpp>
#include <engine/Scene.hpp>
#include <memory>

class Renderer final : public engine::GLProgram
{
  private:
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;
    GLuint m_PVMatID;
    std::shared_ptr<engine::Camera> m_camera;
    uint32_t m_nbTriangles;
    void createVaoVboEbo(const engine::Scene& scene);

  public:
    void render() const;
    Renderer(const engine::PipelineShaderPaths& shaderPaths, const engine::Scene& scene);
    ~Renderer();

    void setViewport(int width, int height);
};
