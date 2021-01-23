#pragma once
#include "EngineSymbols.h"
#include "engine/Scene.hpp"

#include <list>
#include <string>

namespace engine
{
namespace IO
{
/**
 * @brief load meshes at given path
 * @param[in] path Absolute path to mesh file
 * @param[out] scene Loaded scene from file
 * @return true if everything went well
 */
ENGINE_API bool loadScene(const std::string& path, Scene& scene);

} // namespace IO
} // namespace engine
