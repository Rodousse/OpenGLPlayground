#include "engine/Mesh.hpp"

namespace engine
{
Mesh::Mesh(Mesh&& other) noexcept
{
    moveIntoThis(std::move(other));
}

Mesh& Mesh::operator=(Mesh&& other) noexcept
{
    moveIntoThis(std::move(other));
    return *this;
}

void Mesh::refreshBoundingBox()
{
    for(const auto& vertex: vertices)
    {
        Vector3 min = aabb.min.cwiseMin(vertex.pos).eval();
        Vector3 max = aabb.max.cwiseMax(vertex.pos).eval();
        aabb.min = min;
        aabb.max = max;
    }
}

void Mesh::moveIntoThis(Mesh&& other) noexcept
{
    vertices = std::move(other.vertices);
    faces = std::move(other.faces);
    name = std::move(other.name);
    aabb = other.aabb;
}

} // namespace engine
