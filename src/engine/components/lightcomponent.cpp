#include "lightcomponent.h"


LightComponent::LightComponent()
{

}


LightComponent::~LightComponent()
{

}

LightType LightComponent::type() const
{
    return _type;
}

void LightComponent::setLightInterface(LightInterface *lightInterface)
{
	_lightInterface = lightInterface;
}

void LightComponent::setType(LightType type)
{
	_type = type;
	_lightInterface->setType(type);
}

glm::vec4 LightComponent::color() const
{
	return _lightInterface->getColor();
}

void LightComponent::setColor(const glm::vec4& c)
{
	_lightInterface->setColor(c);
}

float LightComponent::intensity() const
{
	return _lightInterface->getIntensity();
}

void LightComponent::setIntensity(float i)
{
	_lightInterface->setIntensity(i);
}

glm::float_t LightComponent::shadowPower() const
{
	return _lightInterface->getShadowPower();
}

void LightComponent::setShadowPower(glm::float_t shadowPower)
{
	_lightInterface->setShadowPower(shadowPower);
}

glm::float_t LightComponent::angle() const
{
	return _lightInterface->getAngle();
}

void LightComponent::setAngle(glm::float_t angle)
{
	_lightInterface->setAngle(angle);
}