#include "cameracomponent.h"

CameraComponent::CameraComponent()
    : _fov(45.0f),
      _aspect(800.0f / 600.0f),
      _nearPlane(1.0f),
      _farPlane(100.0f),
      _clearColor(0.0f, 0.0f, 0.0f)
{
}

CameraComponent::~CameraComponent()
{
}

CameraComponent::PojectionType CameraComponent::projectionType() const
{
    return _type;
}

void CameraComponent::setProjectionType(CameraComponent::PojectionType type)
{
    _type = type;
}

float CameraComponent::fieldOfView() const
{
    return _fov;
}

void CameraComponent::setFieldOfView(const float& fov)
{
    _fov = fov;
}

float CameraComponent::aspect() const
{
    return _aspect;
}

void CameraComponent::setAspect(const float& aspect)
{
    _aspect = aspect;
}

float CameraComponent::nearPlane() const
{
    return _nearPlane;
}

void CameraComponent::setNearPlane(const float& near)
{
    _nearPlane = near;
}

float CameraComponent::farPlane() const
{
    return _farPlane;
}

void CameraComponent::setFarPlane(const float& far)
{
    _farPlane = far;
}

glm::vec3 CameraComponent::clearColor() const
{
    return _clearColor;
}

void CameraComponent::setClearColor(const glm::vec3& cc)
{
    _clearColor = cc;
}