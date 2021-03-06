#include "engine/GLShader.hpp"

#include "engine/GLErrorHandling.hpp"

#include <exception>
#include <fstream>
#include <spdlog/spdlog.h>
#include <unordered_map>

namespace
{
std::vector<char> loadShader(const std::string& path);
}

namespace engine
{
void GLShader::move(GLShader&& other) noexcept
{
    m_shaderObject = other.m_shaderObject;
    other.m_shaderObject = 0;
}

GLShader::GLShader(const std::string& shaderPath, GLenum shaderType): m_shaderType(shaderType)
{
    m_shaderObject = glCreateShader(shaderType);
    const auto shaderContent = ::loadShader(shaderPath);
    if(m_shaderObject == 0 || !CHECK_NO_GL_ERROR)
    {
        throw std::runtime_error("[" + std::string(__FUNCTION__) + "]: Could not create shader object " +
                                 shaderEnumToString(shaderType) + "!");
    }
    const GLchar* sourceContentPointer = shaderContent.data();
    const GLint sourceContentSize = static_cast<GLint>(shaderContent.size());
    glShaderSource(m_shaderObject, 1, &sourceContentPointer, &sourceContentSize);
    if(!CHECK_NO_GL_ERROR)
    {
        glDeleteShader(m_shaderObject);
        throw std::runtime_error("[" + std::string(__FUNCTION__) + "]: Could not set shader source for " +
                                 shaderEnumToString(shaderType) + "!");
    }

    glCompileShader(m_shaderObject);
    GLint flags;
    glGetShaderiv(m_shaderObject, GL_COMPILE_STATUS, &flags);
    if(!CHECK_NO_GL_ERROR || flags == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(m_shaderObject, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(m_shaderObject, maxLength, &maxLength, errorLog.data());

        spdlog::critical("{0} : \n {1}", shaderPath.data(), errorLog.data());

        glDeleteShader(m_shaderObject);
        throw std::runtime_error("[" + std::string(__FUNCTION__) + "]: Shader compilation failed for " +
                                 shaderEnumToString(shaderType) + "!");
    }
}

GLShader::GLShader(GLShader&& other) noexcept
{
    move(std::move(other));
}

GLShader& GLShader::operator=(GLShader&& other) noexcept
{
    move(std::move(other));
    return *this;
}

GLShader::~GLShader()
{
    glDeleteShader(m_shaderObject);
}

GLuint GLShader::id() const
{
    return m_shaderObject;
}

std::string shaderEnumToString(GLenum value)
{
    static const std::unordered_map<GLenum, std::string> lut = {
      {GL_VERTEX_SHADER, "GL_VERTEX_SHADER"},
      {GL_FRAGMENT_SHADER, "GL_FRAGMENT_SHADER"},
      {GL_GEOMETRY_SHADER, "GL_GEOMETRY_SHADER"},
      {GL_TESS_EVALUATION_SHADER, "GL_TESS_EVALUATION_SHADER"},
      {GL_TESS_CONTROL_SHADER, "GL_TESS_CONTROL_SHADER"},
      {GL_COMPUTE_SHADER, "GL_COMPUTE_SHADER"}};

    return lut.at(value);
}

} // namespace engine

namespace
{
std::vector<char> loadShader(const std::string& path)
{
    std::ifstream file;
    file.open(path, std::ios::ate | std::ios::binary);

    if(!file.is_open())
    {
        throw std::runtime_error("[" + std::string(__FUNCTION__) + "] : Can't open shader : " + path);
    }

    const std::streamsize fileSize = file.tellg();

    std::vector<char> shaderData;
    shaderData.resize(static_cast<std::size_t>(fileSize));

    file.seekg(0);
    file.read(shaderData.data(), fileSize);
    file.close();

    return shaderData;
}
} // namespace