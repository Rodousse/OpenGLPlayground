#include "engine/GLErrorHandling.hpp"

#include <spdlog/spdlog.h>
#include <stdexcept>

namespace engine
{
void debugLayerCallback(
  GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    switch(severity)
    {
        case GL_DEBUG_SEVERITY_HIGH: spdlog::critical("Debug Layer : {0}", message); break;
        case GL_DEBUG_SEVERITY_MEDIUM: spdlog::error("Debug Layer : {0}", message); break;
        case GL_DEBUG_SEVERITY_LOW: spdlog::warn("Debug Layer : {0}", message); break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: spdlog::trace("Debug Layer : {0}", message); break;
    }
}

void flushGLErrors()
{
    while(glGetError() != GL_NO_ERROR) {}
}

bool checkNoGLErrors(const char* file, const char* function, int line)
{
    GLenum errorCode{};
    while((errorCode = glGetError()) != GL_NO_ERROR)
    {
        switch(errorCode)
        {
            case GL_INVALID_ENUM:
                spdlog::critical("[{0}], function : {1} l.{2} : {3}", file, function, line, "GL_INVALID_ENUM");
                return false;
            case GL_INVALID_VALUE:
                spdlog::critical("[{0}], function : {1} l.{2} : {3}", file, function, line, "GL_INVALID_VALUE");
                return false;
            case GL_INVALID_OPERATION:
                spdlog::critical("[{0}], function : {1} l.{2} : {3}", file, function, line, "GL_INVALID_OPERATION");
                return false;
            case GL_STACK_OVERFLOW:
                spdlog::critical("[{0}], function : {1} l.{2} : {3}", file, function, line, "GL_STACK_OVERFLOW");
                return false;
            case GL_STACK_UNDERFLOW:
                spdlog::critical("[{0}], function : {1} l.{2} : {3}", file, function, line, "GL_STACK_UNDERFLOW");
                return false;
            case GL_OUT_OF_MEMORY:
                spdlog::critical("[{0}], function : {1} l.{2} : {3}", file, function, line, "GL_OUT_OF_MEMORY");
                return false;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                spdlog::critical(
                  "[{0}], function : {1} l.{2} : {3}", file, function, line, "GL_INVALID_FRAMEBUFFER_OPERATION");
                return false;
            case GL_CONTEXT_LOST:
                spdlog::critical("[{0}], function : {1} l.{2} : {3}", file, function, line, "GL_CONTEXT_LOST");
                return false;
            case GL_TABLE_TOO_LARGE:
                spdlog::critical("[{0}], function : {1} l.{2} : {3}", file, function, line, "GL_TABLE_TOO_LARGE");
                return false;
        }
    }
    return true;
}

} // namespace engine
