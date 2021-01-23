#include "engine/GLErrorHandling.hpp"

#include <stdexcept>

namespace engine
{
void printGLError(
  GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    switch(severity)
    {
        case GL_DEBUG_SEVERITY_HIGH: throw std::runtime_error(message); break;
        case GL_DEBUG_SEVERITY_MEDIUM: break;
        case GL_DEBUG_SEVERITY_LOW: break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: break;
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
