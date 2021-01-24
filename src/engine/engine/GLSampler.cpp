#include "engine/GLSampler.hpp"

namespace engine
{
GLSampler::GLSampler(const SamplerParameters& params)
{
    glGenSamplers(1, &m_samplerID);
}

GLuint GLSampler::id() const
{
    return m_samplerID;
}

GLSampler::~GLSampler()
{
    glDeleteSamplers(1, &m_samplerID);
}

void applySamplerParameters(GLenum samplerID, const SamplerParameters& param)
{
    glSamplerParameterf(samplerID, GL_TEXTURE_LOD_BIAS, param.LODBias);
    glSamplerParameteri(samplerID, GL_TEXTURE_MAG_FILTER, param.magFilter);
    glSamplerParameteri(samplerID, GL_TEXTURE_MIN_FILTER, param.minFilter);
    glSamplerParameteri(samplerID, GL_TEXTURE_MAX_LOD, param.maxLOD);
    glSamplerParameteri(samplerID, GL_TEXTURE_MIN_LOD, param.minLOD);
    glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_R, param.wrapR);
    glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_S, param.wrapS);
    glSamplerParameteri(samplerID, GL_TEXTURE_WRAP_T, param.wrapT);
    glSamplerParameterfv(samplerID, GL_TEXTURE_BORDER_COLOR, param.borderColor.data());
}
} // namespace engine