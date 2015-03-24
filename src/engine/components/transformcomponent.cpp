#include "transformcomponent.h"
#include <glm/gtx/rotate_vector.hpp>

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

glm::vec3 TransformComponent::rotateVector(glm::vec3& vector)
{
	glm::vec3 newVector;
	newVector = glm::rotate(vector, _rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	newVector = glm::rotate(newVector, _rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	newVector = glm::rotate(newVector, _rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	return newVector;
}