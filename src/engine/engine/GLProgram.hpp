#pragma once
#include "EngineSymbols.h"
#include "engine/GLShader.hpp"

#include <GL/glew.h>
#include <string>
#include <unordered_map>
namespace engine
{
struct ENGINE_API PipelineShaderPaths
{
    std::string vertexShader;
    std::string geometryShader;       /// Unsupported
    std::string tessControlShader;    /// Unsupported
    std::string tessEvaluationShader; /// Unsupported
    std::string fragmentShader;
};

class ENGINE_API GLProgram
{
  protected:
    GLuint m_program;
    std::unordered_map<GLenum, GLShader> m_shaders;

    void compileAndLinkShadersToProgram(const PipelineShaderPaths& shaderPaths);
    void move(GLProgram&& other);

  public:
    GLProgram() = delete;
    explicit GLProgram(const PipelineShaderPaths& shaderPaths);
    GLProgram(const GLProgram&) = delete;
    GLProgram& operator=(const GLProgram&) = delete;
    GLProgram(GLProgram&& other) noexcept;
    GLProgram& operator=(GLProgram&& other) noexcept;
    virtual ~GLProgram();

    GLuint handle() const;
};
} // namespace engine
