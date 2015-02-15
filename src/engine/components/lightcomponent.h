#ifndef LIGHT_H
#define LIGHT_H

#include "../global.h"

#include <entityx/Entity.h>
#include <glm/glm.hpp>

class ENGINE_EXPORT LightComponent :
    public entityx::Component<LightComponent>
{
public:
    LightComponent();
    ~LightComponent();

    enum Type
    {
        Directional,
        Point,
        Spot
    };

    Type type() const;
    void setType(Type t);

    glm::vec4 color() const;
    void setColor(const glm::vec4& c);

    float intensity() const;
    void setIntensity(float i);

private:
    Type _type;
    glm::vec4 _color;
    float _intensity;

};

#endif // !LIGHT_H