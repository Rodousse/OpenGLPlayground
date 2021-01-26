#include "engine/PerspectiveCamera.hpp"

#include <iostream>
#include <numeric>
#include <stdexcept>

namespace engine
{
void PerspectiveCamera::refreshProjection()
{
    float yScale = 1.0f / std::tan(m_fov / 2.0f);
    float xScale = yScale / (static_cast<float>(m_viewportDim.x()) / m_viewportDim.y());
    m_proj << xScale, 0.0f, 0.0f, 0.0f, 0.0f, yScale, 0.0f, 0.0f, 0.0f, 0.0f,
      -(m_farClipPlane + m_nearClipPlane) / (m_farClipPlane - m_nearClipPlane),
      -(2.0f * m_nearClipPlane * m_farClipPlane) / (m_farClipPlane - m_nearClipPlane), 0.0f, 0.0f, -1.0f, 0.0f;
}

PerspectiveCamera::PerspectiveCamera(): Camera()
{
    refreshProjection();
}

void PerspectiveCamera::setFovRad(float rad)
{
    if(rad > 2.0f * M_PI || rad < std::numeric_limits<Floating>::epsilon())
    {
        throw(std::invalid_argument("FoV of perspective camera out of range : " + std::to_string(rad) +
                                    " should be in ]0.0;172.0] "));
    }

    m_fov = rad;
    refreshProjection();
}

void PerspectiveCamera::setFovDeg(float deg)
{
    if(deg > 172.0f || deg < std::numeric_limits<Floating>::epsilon())
    {
        throw(std::invalid_argument("FoV of perspective camera out of range : " + std::to_string(deg) +
                                    " should be in ]0.0;172.0] "));
    }

    m_fov = deg * M_PI / 180.0f;
    refreshProjection();
}

float PerspectiveCamera::fov() const
{
    return m_fov;
}

} // namespace engine
