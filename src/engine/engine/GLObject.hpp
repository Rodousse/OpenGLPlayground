#pragma once

#include "EngineSymbols.h"

#include <GL/glew.h>

namespace engine
{
class ENGINE_API GLObject
{
  public:
    GLObject() = default;
    GLObject(const GLObject&) = delete;
    GLObject& operator=(const GLObject&) = delete;
    virtual ~GLObject() = default;
};
} // namespace engine
