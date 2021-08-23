#pragma once
#include <GL/glew.h>
#include <engine/CommonTypes.hpp>
#include <engine/Scene.hpp>
#include <memory>
#include <stdint.h>

class SceneData
{
  private:
    GLuint m_vao{0};
    GLuint m_vbo{0};
    GLuint m_ebo{0};
    uint32_t m_nbFaces{0};

  public:
    SceneData(const engine::Scene& scene);
    SceneData() = delete;
    SceneData(const SceneData&) = delete;
    SceneData(SceneData&&) = default;
    SceneData& operator=(const SceneData&) = delete;
    SceneData& operator=(SceneData&&) = default;
    ~SceneData();

    GLuint vao() const
    {
        return m_vao;
    }
    GLuint vbo() const
    {
        return m_vbo;
    }
    GLuint ebo() const
    {
        return m_ebo;
    }
    uint32_t nbFaces() const
    {
        return m_nbFaces;
    }
};

struct QuadLightData
{
    Vector2 size;
    Vector3 color;
    Vector3 position;
};

