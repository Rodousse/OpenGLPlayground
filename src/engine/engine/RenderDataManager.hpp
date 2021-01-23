#pragma once
#include "EngineSymbols.h"
#include "engine/Mesh.hpp"
#include "engine/RenderData.hpp"

namespace engine
{
ENGINE_API class RenderDataManager
{
  public:
    RenderDataManager() = default;

    void addMesh(const Mesh& mesh);
};
} // namespace engine