#pragma once
#include "EngineSymbols.h"

#include <GL/glew.h>

namespace engine
{
void ENGINE_API debugLayerCallback(
  GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

void ENGINE_API flushGLErrors();

bool ENGINE_API checkNoGLErrors(const char* file, const char* function, int line);

} // namespace engine

#define CHECK_NO_GL_ERROR engine::checkNoGLErrors(__FILE__, __func__, __LINE__)
