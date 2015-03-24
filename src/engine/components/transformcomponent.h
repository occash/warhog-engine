#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "../global.h"
#include "../meta/object.h"

#include <entityx/Entity.h>
#include <glm/glm.hpp>


class ENGINE_EXPORT TransformComponent :
    public entityx::Component<TransformComponent>,
    public Object
{
    U_OBJECT(TransformComponent, Object)
    U_PROPERTIES(
        U_PROPERTY(position, TransformComponent::position, TransformComponent::setPosition),
        U_PROPERTY(rotation, TransformComponent::rotation, TransformComponent::setRotation),
        U_PROPERTY(scale, TransformComponent::scale, TransformComponent::setScale),
    )

public:
    TransformComponent();
    ~TransformComponent();

    glm::vec3 position() const;
    void setPosition(const glm::vec3& pos);

    glm::vec3 rotation() const;
    void setRotation(const glm::vec3& rotate);

    glm::vec3 scale() const;
    void setScale(const glm::vec3& scale);

    glm::vec3 rotateVector(glm::vec3& vector);//return rotated vector
private:
    glm::vec3 _position;
    glm::vec3 _rotation;
    glm::vec3 _scale;

};

#endif