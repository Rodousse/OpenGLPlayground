#pragma once
#include "EngineSymbols.h"
#include "engine/GLObject.hpp"
#include "engine/GLSampler.hpp"

#include <gl/glew.h>

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

class ENGINE_API GLTexture2D : public GLObject
{
  public:
    GLTexture2D(GLint internalFormat,
                int width,
                int height,
                GLenum format,
                GLenum type,
                const void* pixelData,
                const TextureParameters& texParams = {},
                const SamplerParameters& samplerParams = {});
    GLTexture2D(GLint internalFormat,
                int width,
                int height,
                const TextureParameters& texParams = {},
                const SamplerParameters& samplerParams = {});
    ~GLTexture2D() override;
    void setPixelData(GLenum format, GLenum type, const void* pixelData);
    void setPixelData(GLint xOffset, GLint yOffset, GLenum format, GLenum type, const void* pixelData);

    GLuint id();
    int width() const;
    int height() const;

  private:
    GLuint m_textureID;
    int m_width;
    int m_height;
    GLint m_internalFormat;
};

void applyTextureParameters(GLenum target, const TextureParameters& param);

void applySamplerParametersOnTexture(GLenum target, const SamplerParameters& param);

} // namespace engine
