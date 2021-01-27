#pragma once
#include "EngineSymbols.h"
#include "engine/GLObject.hpp"

#include <GL/glew.h>
#include <string>
#include <vector>

namespace engine
{
std::string ENGINE_API shaderEnumToString(GLenum value);

ENGINE_API class GLShader : public GLObject
{
  protected:
    GLuint m_shaderObject{0};
    GLenum m_shaderType;

    void move(GLShader&& other) noexcept;

  public:
    GLShader(const std::string& shaderPath, GLenum shaderType);
    GLShader(GLShader&& other) noexcept;
    GLShader& operator=(GLShader&& other) noexcept;
    ~GLShader() override;

    GLuint id() const;
};

} // namespace engine