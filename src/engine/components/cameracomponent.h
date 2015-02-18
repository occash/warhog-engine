#ifndef CAMERA_H
#define CAMERA_H

#include "../global.h"
#include "../meta/object.h"

#include <entityx/Entity.h>
#include <glm/glm.hpp>

class ENGINE_EXPORT CameraComponent :
    public entityx::Component<CameraComponent>,
    public Object
{
    U_OBJECT(CameraComponent, Object)
    U_PROPERTIES(
        U_PROPERTY(fieldOfView, CameraComponent::fieldOfView, CameraComponent::setFieldOfView),
        U_PROPERTY(aspect, CameraComponent::aspect, CameraComponent::setAspect),
        U_PROPERTY(nearPlane, CameraComponent::nearPlane, CameraComponent::setNearPlane),
        U_PROPERTY(farPlane, CameraComponent::farPlane, CameraComponent::setFarPlane)
    )
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

    float fieldOfView() const;
    void setFieldOfView(const float& fov);

    float aspect() const;
    void setAspect(const float& aspect);

    float nearPlane() const;
    void setNearPlane(const float& near);

    float farPlane() const;
    void setFarPlane(const float& far);

    glm::vec3 clearColor() const;
    void setClearColor(const glm::vec3& cc);

private:
    PojectionType _type;
    float _fov;
    float _aspect;
    float _nearPlane;
    float _farPlane;
    glm::vec3 _clearColor;

};

#endif
