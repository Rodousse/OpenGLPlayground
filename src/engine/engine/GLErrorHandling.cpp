#include "engine/GLErrorHandling.hpp"

#include <spdlog/spdlog.h>
#include <stdexcept>

namespace engine
{
void enableDebugLayer()
{
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(engine::debugLayerCallback, nullptr);
}

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

bool checkNoGLErrors()
{
    return glGetError() == GL_NO_ERROR;
}

} // namespace engine
