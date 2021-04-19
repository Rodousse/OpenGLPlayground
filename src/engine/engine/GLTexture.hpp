#pragma once
#include "EngineSymbols.h"
#include "engine/CommonTypes.hpp"
#include "engine/GLObject.hpp"

#include <GL/glew.h>

namespace engine
{
struct ENGINE_API TextureParameters
{
    GLint baseLevel = 0;
    GLint maxLevel = 1000;
    GLint swizzleR = GL_RED;
    GLint swizzleG = GL_GREEN;
    GLint swizzleB = GL_BLUE;
    GLint swizzleA = GL_ALPHA;
};

struct ENGINE_API SamplerParameters
{
    GLfloat LODBias = 0.0;
    GLint minFilter = GL_NEAREST_MIPMAP_LINEAR;
    GLint magFilter = GL_LINEAR;
    GLint minLOD = -1000;
    GLint maxLOD = 1000;
    GLint wrapS = GL_REPEAT;
    GLint wrapT = GL_REPEAT;
    GLint wrapR = GL_REPEAT;
    Vector4 borderColor = Vector4{0.0f, 0.0f, 0.0f, 0.0f};
};

void applySamplerParameters(GLenum samplerID, const SamplerParameters& param);

void applyTextureParameters(GLenum target, const TextureParameters& param);

void applySamplerParametersOnTexture(GLenum target, const SamplerParameters& param);

} // namespace engine
