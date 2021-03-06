#pragma once

#include <engine/GLProgram.hpp>
#include <engine/Scene.hpp>
#include <memory>

class Renderer final : public engine::GLProgram
{
  public:
    struct LightMaterial
    {
        Vector3 lightPosition{0.0f, 0.0f, 0.0f};
        float lightIntensity{1000.0f};
        Vector3 lightDiffuseColor{1.0f, 1.0f, 1.0f};
        float materialSpecularity{5.0f};
        Vector3 lightAmbientColor{0.0f, 0.0f, 0.0f};
        float _1;
        Vector3 lightSpecularColor{1.0f, 1.0f, 1.0f};
        float _2;
        Vector3 materialColor{1.0f, 1.0f, 1.0f};
    };
    void render() const;
    Renderer(const engine::PipelineShaderPaths& shaderPaths, const engine::Scene& scene);
    ~Renderer();

    void setViewport(int width, int height);
    void setLightMaterial(const LightMaterial& lightMat);

  private:
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;
    GLuint m_ubo;
    GLuint m_PVMatID;
    GLuint m_VIMatID;
    std::shared_ptr<engine::Camera> m_camera;
    uint32_t m_nbTriangles;

    void createVaoVboEbo(const engine::Scene& scene);
    void createUbo();
};
