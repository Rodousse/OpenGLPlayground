#include "engine/GLTexture.hpp"

#include "engine/GLErrorHandling.hpp"

namespace engine
{
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

void applyTextureParameters(GLenum target, const TextureParameters& param)
{
    glTexParameteri(target, GL_TEXTURE_BASE_LEVEL, param.baseLevel);
    glTexParameteri(target, GL_TEXTURE_MAX_LEVEL, param.maxLevel);
    glTexParameteri(target, GL_TEXTURE_SWIZZLE_B, param.swizzleB);
    glTexParameteri(target, GL_TEXTURE_MAX_LOD, param.swizzleG);
    glTexParameteri(target, GL_TEXTURE_MIN_LOD, param.swizzleR);
}

void applySamplerParametersOnTexture(GLenum target, const SamplerParameters& param)
{
    glTexParameterf(target, GL_TEXTURE_LOD_BIAS, param.LODBias);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, param.magFilter);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, param.minFilter);
    glTexParameteri(target, GL_TEXTURE_MAX_LOD, param.maxLOD);
    glTexParameteri(target, GL_TEXTURE_MIN_LOD, param.minLOD);
    glTexParameteri(target, GL_TEXTURE_WRAP_R, param.wrapR);
    glTexParameteri(target, GL_TEXTURE_WRAP_S, param.wrapS);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, param.wrapT);
    glTexParameterfv(target, GL_TEXTURE_BORDER_COLOR, param.borderColor.data());
}

} // namespace engine