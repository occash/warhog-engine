#include "lightcomponent.h"


LightComponent::LightComponent()
{
}


LightComponent::~LightComponent()
{
}

LightComponent::Type LightComponent::type() const
{
    return _type;
}

void LightComponent::setType(Type t)
{
    _type = t;
}

glm::vec4 LightComponent::color() const
{
    return _color;
}

void LightComponent::setColor(const glm::vec4& c)
{
    _color = c;
}

glm::float_t LightComponent::intensity() const
{
    return _intensity;
}

void LightComponent::setIntensity(glm::float_t i)
{
    _intensity = i;
}
