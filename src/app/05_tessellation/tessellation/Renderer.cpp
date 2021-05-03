#include "tessellation/Renderer.hpp"

#include "engine/CommonTypes.hpp"
#include "engine/GLTexture.hpp"
#include "stbipp/Color.hpp"
#include "stbipp/Image.hpp"
#include "stbipp/ImageFormat.hpp"
#include "stbipp/ImageImporter.hpp"

#include <Eigen/Dense>
#include <GL/glew.h>
#include <array>
#include <engine/GLErrorHandling.hpp>

void Renderer::createVaoVboEbo(const engine::Scene& scene)
{
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 scene.meshes[0]->vertices.size() * sizeof(scene.meshes[0]->vertices[0]),
                 scene.meshes[0]->vertices.data(),
                 GL_STATIC_DRAW);

    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 scene.meshes[0]->faces.size() * sizeof(scene.meshes[0]->faces[0]),
                 scene.meshes[0]->faces.data(),
                 GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        {
            // position
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(engine::Vertex), nullptr);
            // normals
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(
              1, 3, GL_FLOAT, GL_FALSE, sizeof(engine::Vertex), (void*)offsetof(engine::Vertex, normal));
            // UV
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(
              2, 2, GL_FLOAT, GL_FALSE, sizeof(engine::Vertex), (void*)offsetof(engine::Vertex, uv));
            // tangent
            glEnableVertexAttribArray(3);
            glVertexAttribPointer(
              3, 3, GL_FLOAT, GL_FALSE, sizeof(engine::Vertex), (void*)offsetof(engine::Vertex, tangent));
            // bitangent
            glEnableVertexAttribArray(4);
            glVertexAttribPointer(
              4, 3, GL_FLOAT, GL_FALSE, sizeof(engine::Vertex), (void*)offsetof(engine::Vertex, bitangent));
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    }
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glUseProgram(m_program);
    m_PVMatID = glGetUniformLocation(m_program, "PV_mat");
    m_lightDirID = glGetUniformLocation(m_program, "lightDir");
    const auto heightMapID = glGetUniformLocation(m_program, "heightMap");
    glUniform1i(heightMapID, 0);
    const auto normalMapID = glGetUniformLocation(m_program, "normalMap");
    glUniform1i(normalMapID, 1);
    const auto diffuseMapID = glGetUniformLocation(m_program, "diffuseMap");
    glUniform1i(diffuseMapID, 2);
    m_displacementAmplitudeID = glGetUniformLocation(m_program, "displacementAmplitude");
    glUniform1f(m_displacementAmplitudeID, 10.0f);
    glUseProgram(0);
    THROW_IF_GL_ERROR;
}
void Renderer::createTextures(const MaterialMaps& maps)
{
    engine::SamplerParameters sampleParams{};
    sampleParams.minFilter = GL_LINEAR;
    engine::TextureParameters textureParams{};
    // [0] height, [1] normal, [2] diffuse
    std::array<GLuint, 3> textures{};
    glGenTextures(textures.size(), textures.data());
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    {
        stbipp::Image textureData{};
        stbipp::loadImage(maps.height, textureData, stbipp::ImageFormat::LUM8);
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_R8,
                     textureData.width(),
                     textureData.height(),
                     0,
                     GL_RED,
                     GL_UNSIGNED_BYTE,
                     textureData.castData<stbipp::Coloruc>().data());
        applySamplerParametersOnTexture(GL_TEXTURE_2D, sampleParams);
        applyTextureParameters(GL_TEXTURE_2D, textureParams);
    }
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    {
        stbipp::Image textureData{};
        stbipp::loadImage(maps.normal, textureData, stbipp::ImageFormat::RGB8);
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_RGB8,
                     textureData.width(),
                     textureData.height(),
                     0,
                     GL_RGB,
                     GL_UNSIGNED_BYTE,
                     textureData.castData<stbipp::Color3uc>().data());
        applySamplerParametersOnTexture(GL_TEXTURE_2D, sampleParams);
        applyTextureParameters(GL_TEXTURE_2D, textureParams);
    }
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    {
        stbipp::Image textureData{};
        stbipp::loadImage(maps.color, textureData, stbipp::ImageFormat::RGB8);
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_RGB8,
                     textureData.width(),
                     textureData.height(),
                     0,
                     GL_RGB,
                     GL_UNSIGNED_BYTE,
                     textureData.castData<stbipp::Color3uc>().data());
        applySamplerParametersOnTexture(GL_TEXTURE_2D, sampleParams);
        applyTextureParameters(GL_TEXTURE_2D, textureParams);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    m_heightTexture = textures[0];
    m_normalTexture = textures[1];
    m_diffuseTexture = textures[2];
    if(!CHECK_NO_GL_ERROR)
    {
        throw std::runtime_error("Could not create texture object");
    }
}

void Renderer::render() const
{
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glEnable(GL_DEPTH_TEST);
    glUseProgram(m_program);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_heightTexture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_normalTexture);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, m_diffuseTexture);
    glBindVertexArray(m_vao);
    glDrawElements(GL_PATCHES, m_nbTriangles, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

    glUseProgram(0);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    THROW_IF_GL_ERROR;
}

Renderer::Renderer(const engine::PipelineShaderPaths& shaderPaths,
                   const engine::Scene& scene,
                   const MaterialMaps& maps):
  engine::GLProgram(shaderPaths), m_camera(scene.cameras[0]), m_nbTriangles(scene.meshes[0]->faces.size() * 3)
{
    createVaoVboEbo(scene);
    createTextures(maps);
    const auto& viewport = m_camera->getViewportDimension();
    setViewport({0, 0, viewport.x(), viewport.y()});
    setDirectionnalLightDir(Vector3::Identity());
    glPolygonMode(GL_FRONT, GL_LINE);
    glPatchParameteri(GL_PATCH_VERTICES, 3);
}

Renderer::~Renderer()
{
    std::array<GLuint, 2> texs{{m_heightTexture, m_normalTexture}};
    glDeleteTextures(2, texs.data());
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
    glDeleteVertexArrays(1, &m_vao);
}

void Renderer::setViewport(const engine::Viewport& viewport)
{
    if(m_viewport.width == viewport.width && m_viewport.height == viewport.height)
    {
        return;
    }
    m_viewport = viewport;
    m_camera->setViewportDimensions(viewport.width, viewport.height);
    const auto PV = m_camera->getProjection() * m_camera->getView();

    glViewport(0, 0, viewport.width, viewport.height);
    glUseProgram(m_program);
    glUniformMatrix4fv(m_PVMatID, 1, GL_FALSE, PV.eval().data());
    glUseProgram(0);
}

void Renderer::setDirectionnalLightDir(const Vector3& dir)
{
    glUseProgram(m_program);
    glUniform3fv(m_lightDirID, 1, dir.normalized().data());
    glUseProgram(0);
}

void Renderer::setPolygonMode(GLenum mode)
{
    glPolygonMode(GL_FRONT, mode);
}
void Renderer::setDisplacementAmplitude(float amplitude)
{
    glUseProgram(m_program);
    glUniform1f(m_displacementAmplitudeID, amplitude);
    glUseProgram(0);
}
