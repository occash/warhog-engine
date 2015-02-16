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
        U_PROPERTY(position, position, setPosition),
        U_PROPERTY(rotation, rotation, setRotation),
        U_PROPERTY(scale, scale, setScale),
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

private:
    glm::vec3 _position;
    glm::vec3 _rotation;
    glm::vec3 _scale;

};

#endif