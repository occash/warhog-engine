#include "transformcomponent.h"


TransformComponent::TransformComponent()
    : _scale(1.0f, 1.0f, 1.0f)
{
}


TransformComponent::~TransformComponent()
{
}

glm::vec3 TransformComponent::position() const
{
    return _position;
}

void TransformComponent::setPosition(const glm::vec3& pos)
{
    _position = pos;
}

glm::vec3 TransformComponent::rotation() const
{
    return _rotation;
}

void TransformComponent::setRotation(const glm::vec3& rotate)
{
    _rotation = rotate;
}

glm::vec3 TransformComponent::scale() const
{
    return _scale;
}

void TransformComponent::setScale(const glm::vec3& scale)
{
    _scale = scale;
}