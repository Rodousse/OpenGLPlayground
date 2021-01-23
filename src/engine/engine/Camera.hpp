#pragma once
#include "EngineSymbols.h"
#include "engine/CommonTypes.hpp"

#include <memory>
#include <vector>

namespace engine
{
class ENGINE_API Camera
{
  protected:
    Vector3 m_position = Vector3::Zero();
    Matrix3 m_rotation = Matrix3::Identity();

    // Frustum information
    float m_nearClipPlane = 0.1f;
    float m_farClipPlane = 100.0f;

    Matrix4 m_view = Matrix4::Identity();
    Matrix4 m_proj = Matrix4::Identity();

    Vector3 m_forward;
    Vector3 m_right;
    Vector3 m_up;
    Vector3 m_upWorld;

    Eigen::Vector2i m_viewportDim;
    Eigen::Vector2i m_viewportPos = Eigen::Vector2i::Zero();

    void refreshPosition();
    void refreshRotation();
    virtual void refreshProjection() = 0;

  public:
    Camera();
    virtual ~Camera() = default;
    void lookAt(const Vector3& position, const Vector3& center, const Vector3& up);

    void setViewportDimensions(Eigen::Vector2i dim);
    void setViewportDimensions(int width, int height);
    Eigen::Vector2i getViewportDimension();

    void setFarClipPlane(float far);
    void setNearClipPlane(float near);

    float getFarClipPlane() const;
    float getNearClipPlane() const;

    const Matrix4& getView() const;
    void setView(const Matrix4& view);

    const Matrix4& getProjection() const;

    void setPosition(const Vector3& pos);
    const Vector3& getPosition() const;

    void setRotation(const Matrix3& rotation);
    const Matrix3& getRotation() const;
};

} // namespace engine
