#pragma once
#include "EngineSymbols.h"
#include "engine/CommonTypes.hpp"
#include "engine/GLObject.hpp"

#include <gl/glew.h>

namespace engine
{
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

class ENGINE_API GLSampler : public GLObject
{
  public:
    GLSampler(const SamplerParameters& params);
    ~GLSampler();

    GLuint id() const;

  private:
    GLuint m_samplerID;
};

void applySamplerParameters(GLenum samplerID, const SamplerParameters& param);
} // namespace engine
