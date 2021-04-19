#include "fbo/GRenderer.hpp"

#include <engine/GLErrorHandling.hpp>

GRenderer::GRenderer(const engine::PipelineShaderPaths& shaderPaths, const engine::Scene& scene):
  engine::GLProgram(shaderPaths), m_camera(scene.cameras[0]), m_indices(scene.meshes[0]->faces.size() * 3)
{
    createVaoVboEbo(scene);
    refreshUniforms();
    glGenFramebuffers(1, &m_fbo);
    THROW_IF_GL_ERROR;
}
GRenderer::~GRenderer()
{
    if(m_fbo)
    {
        glDeleteFramebuffers(1, &m_fbo);
    }
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
    glDeleteVertexArrays(1, &m_vao);
}

void GRenderer::render() const
{
    std::array<GLenum, 2> buffers = {{GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1}};
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glUseProgram(m_program);
    glDrawBuffers(buffers.size(), buffers.data());
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_indices, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

    glUseProgram(0);
    glDisable(GL_CULL_FACE);
    THROW_IF_GL_ERROR;
}
GLuint GRenderer::gbufferFbo() const
{
    return m_fbo;
}

void GRenderer::linkAttachmentTexturesToFbo(const GBufferTextures& targets) const
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    for(const auto& attachment: targets)
    {
        glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, attachment.second.attachment, GL_TEXTURE_2D, attachment.first, 0);
        THROW_IF_GL_ERROR;
    }
    if(glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        throw std::runtime_error("Could not create framebuffer in GRenderer!");
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    THROW_IF_GL_ERROR;
}
void GRenderer::createVaoVboEbo(const engine::Scene& scene)
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
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    }
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glUseProgram(m_program);
    m_PVMatID = glGetUniformLocation(m_program, "PV_mat");
    const auto PVMat = m_camera->getProjection() * m_camera->getView();
    glUniformMatrix4fv(m_PVMatID, 1, GL_FALSE, PVMat.eval().data());
    glUseProgram(0);

    THROW_IF_GL_ERROR;
}

void GRenderer::refreshUniforms() const
{
    glUseProgram(m_program);
    const auto PVMat = m_camera->getProjection() * m_camera->getView();
    glUniformMatrix4fv(m_PVMatID, 1, GL_FALSE, PVMat.eval().data());
    glUseProgram(0);
}
