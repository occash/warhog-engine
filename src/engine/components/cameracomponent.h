#ifndef CAMERA_H
#define CAMERA_H

#include "../global.h"

#include <entityx/Entity.h>
#include <glm/glm.hpp>

class ENGINE_EXPORT CameraComponent : 
	public entityx::Component<CameraComponent>
{
public:
	enum PojectionType
	{
		Perspective,
		Ortho,
		Custom
	};

    CameraComponent();
    ~CameraComponent();

	PojectionType projectionType() const;
	void setProjectionType(PojectionType type);

	glm::float_t fieldOfView() const;
	void setFieldOfView(const glm::float_t& fov);

	glm::float_t aspect() const;
	void setAspect(const glm::float_t& aspect);

	glm::float_t nearPlane() const;
	void setNearPlane(const glm::float_t& near);

	glm::float_t farPlane() const;
	void setFarPlane(const glm::float_t&far);

	glm::vec3 clearColor() const;
	void setClearColor(const glm::vec3& cc);

private:
	PojectionType _type;
    glm::float_t _fov;
	glm::float_t _aspect;
	glm::float_t _nearPlane;
	glm::float_t _farPlane;
	glm::vec3 _clearColor;

};

#endif
