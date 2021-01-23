#pragma once
#include "engine/Camera.hpp"

namespace engine
{
class ENGINE_API PerspectiveCamera : public Camera
{
  protected:
    float m_fov = M_PI / 2.0f;
    void refreshProjection() override;

  public:
    PerspectiveCamera();
    ~PerspectiveCamera() override = default;

    void setFovDeg(float deg);
    void setFovRad(float rad);
    float fov() const;
};

} // namespace engine
