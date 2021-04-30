
#include "fbo/ShadingRenderer.hpp"

#include "fbo/Types.hpp"

#include <engine/GLErrorHandling.hpp>

ShadingRenderer::ShadingRenderer(const engine::PipelineShaderPaths& paths, const engine::Scene& scene):
  engine::GLProgram(paths), m_camera(scene.cameras[0])
{
    createVaoVboEbo();
    createUbo();
}
ShadingRenderer::~ShadingRenderer()
{
    glDeleteBuffers(1, &m_ubo);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
    glDeleteVertexArrays(1, &m_vao);
}

void ShadingRenderer::render(const GBufferTextures& targets) const
{
    glUseProgram(m_program);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, getAttachmentTextureFromGBufferTextures(targets, GBufferAttachment::Position));
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, getAttachmentTextureFromGBufferTextures(targets, GBufferAttachment::Normal));
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

    glUseProgram(0);
    THROW_IF_GL_ERROR;
}

void ShadingRenderer::createVaoVboEbo()
{
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(m_vertices[0]), m_vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(m_indices[0]), m_indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        {
            // position
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(m_vertices[0]), nullptr);
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    }
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glUseProgram(m_program);
    m_camPositionID = glGetUniformLocation(m_program, "camPosition");
    const auto normalID = glGetUniformLocation(m_program, "gbufferNormal");
    glUniform1i(normalID, 1);
    const auto positionID = glGetUniformLocation(m_program, "gbufferPosition");
    glUniform1i(positionID, 0);
    glUniform3fv(m_camPositionID, 1, m_camera->getPosition().data());
    glUseProgram(0);

    THROW_IF_GL_ERROR;
}

void ShadingRenderer::createUbo()
{
    glGenBuffers(1, &m_ubo);

    const auto blockIndex = glGetUniformBlockIndex(m_program, "UBOData");
    glUniformBlockBinding(m_program, blockIndex, 0);

    glUseProgram(m_program);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_ubo);
    glUseProgram(0);
    THROW_IF_GL_ERROR;
}
void ShadingRenderer::setLightMaterial(const LightMaterial& lightMat)
{
    glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(LightMaterial), &lightMat, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    THROW_IF_GL_ERROR;
}
