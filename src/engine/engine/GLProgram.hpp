#pragma once
#include "EngineSymbols.h"
#include "engine/GLObject.hpp"
#include "engine/GLShader.hpp"

#include <GL/glew.h>
#include <string>
#include <unordered_map>
namespace engine
{
struct ENGINE_API PipelineShaderPaths
{
    std::string vertexShader;
    std::string geometryShader; /// Unsupported
    std::string tessControlShader;
    std::string tessEvaluationShader;
    std::string fragmentShader;
};

class ENGINE_API GLProgram : public GLObject
{
  protected:
    GLuint m_program;
    std::unordered_map<GLenum, GLShader> m_shaders;

    void compileAndLinkShadersToProgram(const PipelineShaderPaths& shaderPaths);
    void move(GLProgram&& other);

  public:
    explicit GLProgram(const PipelineShaderPaths& shaderPaths);
    GLProgram(GLProgram&& other) noexcept;
    GLProgram& operator=(GLProgram&& other) noexcept;
    ~GLProgram() override;

    GLuint id() const;
};
} // namespace engine
