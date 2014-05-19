#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "../global.h"

#include <glm/glm.hpp>
#include <entityx/Entity.h>

using namespace entityx;

class ENGINE_EXPORT TransformComponent : public Component<TransformComponent>
{
public:
	TransformComponent();
	~TransformComponent();

	glm::vec3 position() const;
	void setPosition(const glm::vec3& pos);

	glm::vec3 rotation() const;
	void setRotation(const glm::vec3& rotate);

	glm::vec3 scale() const;
	void setScale(const glm::vec3& scale);

private:
	glm::vec3 _position;
	glm::vec3 _rotation;
	glm::vec3 _scale;

};

#endif