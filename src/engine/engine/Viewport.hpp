#pragma once

#include "EngineSymbols.h"

#include <GL/glew.h>
namespace engine
{
struct ENGINE_API Viewport
{
    GLint x{0};
    GLint y{0};
    GLsizei width{};
    GLsizei height{};
};
} // namespace engine
