#include "engine/Camera.hpp"

#include <Eigen/Geometry>
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdexcept>

namespace engine
{
void Camera::refreshPosition()
{
    m_view.block<3, 1>(0, 3) = Vector3{-m_right.dot(m_position), -m_up.dot(m_position), m_forward.dot(m_position)};
}

void Camera::refreshRotation()
{
    m_view.block<3, 3>(0, 0) = m_rotation;
}

Camera::Camera()
{
    refreshPosition();
    refreshRotation();
}

void Camera::lookAt(const Vector3& position, const Vector3& center, const Vector3& up)
{
    m_position = position;
    m_upWorld = up.normalized();

    m_forward = (center - position).normalized();
    m_right = m_forward.cross(m_upWorld).normalized();
    m_up = m_right.cross(m_forward).normalized();

    m_rotation.row(0) = m_right;
    m_rotation.row(1) = m_up;
    m_rotation.row(2) = -m_forward;

    refreshRotation();
    refreshPosition();
}

void Camera::setViewportDimensions(Eigen::Vector2i dim)
{
    m_viewportDim = dim;
    refreshProjection();
}
void Camera::setViewportDimensions(int width, int height)
{
    setViewportDimensions({width, height});
}

Eigen::Vector2i Camera::getViewportDimension()
{
    return m_viewportDim;
}

const Matrix4& Camera::getView() const
{
    return m_view;
}

void Camera::setView(const Matrix4& view)
{
    m_view = view;
}

const Matrix4& Camera::getProjection() const
{
    return m_proj;
}

void Camera::setFarClipPlane(float far)
{
    m_farClipPlane = far;
    refreshProjection();
}
void Camera::setNearClipPlane(float near)
{
    m_nearClipPlane = near;
    refreshProjection();
}

float Camera::getFarClipPlane() const
{
    return m_farClipPlane;
}
float Camera::getNearClipPlane() const
{
    return m_nearClipPlane;
}

void Camera::setPosition(const Vector3& pos)
{
    m_position = pos;
    refreshPosition();
}
const Vector3& Camera::getPosition() const
{
    return m_position;
}

void Camera::setRotation(const Matrix3& rotation)
{
    m_rotation = rotation;
    refreshRotation();
}
const Matrix3& Camera::getRotation() const
{
    return m_rotation;
}
} // namespace engine
