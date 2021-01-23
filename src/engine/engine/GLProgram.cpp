#include "engine/GLProgram.hpp"

#include "engine/GLErrorHandling.hpp"

#include <GL/glew.h>
#include <unordered_map>

namespace engine
{
GLProgram::GLProgram(const PipelineShaderPaths& shaderPaths)
{
    compileAndLinkShadersToProgram(shaderPaths);
}

GLProgram::GLProgram(GLProgram&& other) noexcept
{
    move(std::move(other));
}

GLProgram& GLProgram::operator=(GLProgram&& other) noexcept
{
    move(std::move(other));
    return *this;
}

GLProgram::~GLProgram()
{
    if(m_program != 0)
    {
        glDeleteProgram(m_program);
    }
}

GLuint GLProgram::handle() const
{
    return m_program;
}

void GLProgram::compileAndLinkShadersToProgram(const PipelineShaderPaths& shaderPaths)
{
    if(shaderPaths.fragmentShader.empty())
    {
        throw std::runtime_error("[" + std::string(__FUNCTION__) + "]: Fragment shader has no path set!");
    }
    if(shaderPaths.vertexShader.empty())
    {
        throw std::runtime_error("[" + std::string(__FUNCTION__) + "]: Vertex shader has no path set!");
    }
    std::unordered_map<GLenum, const std::string*> shaders = {{GL_VERTEX_SHADER, &shaderPaths.vertexShader},
                                                              {GL_FRAGMENT_SHADER, &shaderPaths.fragmentShader}};

    m_program = glCreateProgram();
    if(m_program == 0)
    {
        throw std::runtime_error("[" + std::string(__FUNCTION__) + "]: Could not create the pipeline!");
    }

    for(const auto& shader: shaders)
    {
        if(shader.second->empty())
        {
            continue;
        }
        const auto& newShader = m_shaders.emplace(shader.first, GLShader(*(shader.second), shader.first)).first->second;
        glAttachShader(m_program, newShader.handle());
        if(!checkNoGLErrors())
        {
            throw std::runtime_error("[" + std::string(__FUNCTION__) + "]: Can't attach shader " +
                                     shaderEnumToString(shader.first) + " to the program!");
        }
    }

    glLinkProgram(m_program);
    if(!checkNoGLErrors())
    {
        throw std::runtime_error("[" + std::string(__FUNCTION__) + "]: Can't link shaders to program!");
    }
}

void GLProgram::move(GLProgram&& other)
{
    m_shaders.swap(other.m_shaders);
    m_program = other.m_program;
    other.m_program = 0;
}

} // namespace engine