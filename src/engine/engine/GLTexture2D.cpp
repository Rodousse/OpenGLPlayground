#include "engine/GLTexture2D.hpp"

namespace engine
{
GLTexture2D::GLTexture2D(GLint internalFormat,
                         int width,
                         int height,
                         GLenum format,
                         GLenum type,
                         const void* pixelData,
                         const TextureParameters& texParams,
                         const SamplerParameters& samplerParams):
  m_width(width), m_height(height), m_internalFormat(internalFormat)
{
    if(!pixelData)
    {
        throw std::runtime_error(std::string(__FUNCTION__) + ": Specified nullptr on texture data transfer");
    }
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    {
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, pixelData);
        applySamplerParametersOnTexture(GL_TEXTURE_2D, samplerParams);
        applyTextureParameters(GL_TEXTURE_2D, texParams);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLTexture2D::GLTexture2D(GLint internalFormat,
                         int width,
                         int height,
                         const TextureParameters& texParams,
                         const SamplerParameters& samplerParams):
  m_width(width), m_height(height), m_internalFormat(internalFormat)
{
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    {
        glTexStorage2D(GL_TEXTURE_2D, 1, internalFormat, width, height);
        applySamplerParametersOnTexture(GL_TEXTURE_2D, samplerParams);
        applyTextureParameters(GL_TEXTURE_2D, texParams);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLTexture2D::~GLTexture2D()
{
    glDeleteTextures(1, &m_textureID);
}

void GLTexture2D::setPixelData(GLenum format, GLenum type, const void* pixelData)
{
    setPixelData(0, 0, format, type, pixelData);
}

void GLTexture2D::setPixelData(GLint xOffset, GLint yOffset, GLenum format, GLenum type, const void* pixelData)
{
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    {
        glTexSubImage2D(GL_TEXTURE_2D, 0, xOffset, yOffset, m_width, m_height, format, type, pixelData);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint GLTexture2D::id()
{
    return m_textureID;
}

int GLTexture2D::width() const
{
    return m_width;
}

int GLTexture2D::height() const
{
    return m_height;
}

void applyTextureParameters(GLenum target, const TextureParameters& param)
{
    glTexParameterf(target, GL_TEXTURE_BASE_LEVEL, param.baseLevel);
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