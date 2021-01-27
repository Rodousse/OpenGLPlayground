#pragma once
#include "EngineSymbols.h"

#include <GL/glew.h>

namespace engine
{
void ENGINE_API enableDebugLayer();

void ENGINE_API debugLayerCallback(
  GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

void ENGINE_API flushGLErrors();

bool ENGINE_API checkNoGLErrors();
} // namespace engine