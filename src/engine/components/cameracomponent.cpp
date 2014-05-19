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

glm::float_t CameraComponent::fieldOfView() const
{
	return _fov;
}

void CameraComponent::setFieldOfView(const glm::float_t& fov)
{
	_fov = fov;
}

glm::float_t CameraComponent::aspect() const
{
	return _aspect;
}

void CameraComponent::setAspect(const glm::float_t& aspect)
{
	_aspect = aspect;
}

glm::float_t CameraComponent::nearPlane() const
{
	return _nearPlane;
}

void CameraComponent::setNearPlane(const glm::float_t& near)
{
	_nearPlane = near;
}

glm::float_t CameraComponent::farPlane() const
{
	return _farPlane;
}

void CameraComponent::setFarPlane(const glm::float_t& far)
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