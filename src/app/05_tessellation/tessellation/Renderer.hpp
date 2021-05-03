#pragma once

#include <engine/GLProgram.hpp>
#include <engine/Scene.hpp>
#include <engine/Viewport.hpp>
#include <memory>

class Renderer final : public engine::GLProgram
{
  public:
    struct MaterialMaps
    {
        std::string color{};
        std::string height{};
        std::string normal{};
    };

  private:
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;
    GLuint m_heightTexture;
    GLuint m_normalTexture;
    GLuint m_diffuseTexture;
    GLuint m_PVMatID;
    GLuint m_lightDirID;
    GLuint m_displacementAmplitudeID;
    std::shared_ptr<engine::Camera> m_camera;
    uint32_t m_nbTriangles;
    engine::Viewport m_viewport;

    void createVaoVboEbo(const engine::Scene& scene);
    void createTextures(const MaterialMaps& maps);

  public:
    void render() const;
    Renderer(const engine::PipelineShaderPaths& shaderPaths, const engine::Scene& scene, const MaterialMaps& maps);
    ~Renderer();

    void setViewport(const engine::Viewport& viewport);
    void setDirectionnalLightDir(const Vector3& dir);
    void setPolygonMode(GLenum mode);
    void setDisplacementAmplitude(float amplitude);
};
