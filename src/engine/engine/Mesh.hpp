#pragma once
#include "EngineSymbols.h"
#include "engine/CommonTypes.hpp"

#include <Eigen/Dense>
#include <array>
#include <memory>
#include <vector>
namespace engine
{
/// Used for mesh vertex indexing
using FaceIndex = uint32_t;

/// Used for mesh vertex indexing
using VertexIndex = uint32_t;

/// Triangle face vertex indices
using FaceIndices = std::array<VertexIndex, 3>;

/**
 * @brief Axis aligned bounding box
 */
struct ENGINE_API AABoundingBox
{
    Vector3 min{
      std::numeric_limits<Floating>::max(), std::numeric_limits<Floating>::max(), std::numeric_limits<Floating>::max()};
    Vector3 max{std::numeric_limits<Floating>::lowest(),
                std::numeric_limits<Floating>::lowest(),
                std::numeric_limits<Floating>::lowest()};
};

/**
 * @brief Vertex description
 */
struct ENGINE_API Vertex
{
    Vector3 pos{};
    Vector3 normal{};
    Vector2 uv{};
};

/**
 * @brief Mesh description
 */
struct ENGINE_API Mesh
{
    Mesh() = default;
    Mesh(const Mesh& other) = default;
    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(const Mesh& other) = default;
    Mesh& operator=(Mesh&& other) noexcept;
    ~Mesh() = default;

    std::vector<Vertex> vertices{};
    std::vector<FaceIndices> faces{};
    std::string name{};
    AABoundingBox aabb{};

    void refreshBoundingBox();

  private:
    void moveIntoThis(Mesh&& other) noexcept;
};

} // namespace engine
