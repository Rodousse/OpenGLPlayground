#pragma once
#include "EngineSymbols.h"
#include "engine/Camera.hpp"
#include "engine/Mesh.hpp"

#include <vector>

namespace engine
{
struct ENGINE_API Scene
{
    std::vector<std::shared_ptr<Camera>> cameras{};
    std::vector<std::shared_ptr<Mesh>> meshes{};

    Vector3 backgroundColor{1.0, 1.0, 1.0};
};

} // namespace engine
