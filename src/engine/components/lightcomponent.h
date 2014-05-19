#ifndef LIGHT_H
#define LIGHT_H

#include "../global.h"

#include <glm/glm.hpp>
#include <entityx/Entity.h>

using namespace entityx;

class ENGINE_EXPORT LightComponent : public Component<LightComponent>
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

    glm::float_t intensity() const;
    void setIntensity(glm::float_t i);

private:
    Type _type;
    glm::vec4 _color;
    glm::float_t _intensity;
    
};

#endif // !LIGHT_H