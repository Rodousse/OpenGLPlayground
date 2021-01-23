#pragma once
#include "EngineSymbols.h"

#include <GL/glew.h>
#include <string>
#include <vector>

namespace engine
{
std::string ENGINE_API shaderEnumToString(GLenum value);

ENGINE_API class GLShader
{
  protected:
    GLuint m_shaderObject = 0;
    std::vector<char> m_shaderContent;

    void move(GLShader&& other) noexcept;

  public:
    GLShader() = delete;
    GLShader(const std::string& shaderPath, GLenum shaderType);
    GLShader(const GLShader&) = delete;
    GLShader& operator=(const GLShader&) = delete;
    GLShader(GLShader&& other) noexcept;
    GLShader& operator=(GLShader&& other) noexcept;
    ~GLShader();

    GLuint handle() const;
};

} // namespace engine