#include "lightinterface.h"

LightInterface::LightInterface()
{

}

LightInterface::LightInterface(DirectLight *directLight) : _directLight(directLight), _type(LightType::Directional)
{
	
}

LightInterface::LightInterface(PointLight *pointLight) : _pointLight(pointLight), _type(LightType::Point)
{

}

LightInterface::LightInterface(SpotLight *spotLight) : _spotLight(spotLight), _type(LightType::Spot)
{

}

glm::vec4 LightInterface::getPosition() const
{
	switch (_type)
	{
	case Point:
		return _pointLight->position;
	case Spot:
		return _spotLight->position;
	default:
		return glm::vec4{0, 0, 0, 0 }; // think about default value
	}
}

glm::vec4 LightInterface::getColor() const
{
	switch (_type)
	{
	case Directional:
		return _directLight->color;
	case Point:
		return _pointLight->color;
	case Spot:
		return _spotLight->color;
	default:
		return glm::vec4{ 0, 0, 0, 0 }; // think about default value
	}
}

glm::vec4 LightInterface::getDirection() const
{
	switch (_type)
	{
	case Directional:
		return _directLight->direction;
	case Spot:
		return _spotLight->direction;
	default:
		return glm::vec4{0, 0, 0, 0}; // think about default value
	}
}

glm::float_t LightInterface::getAngle() const
{
	if (_type == LightType::Spot)
		return _spotLight->angle;

	return 0; // think about default value
}

glm::float_t LightInterface::getShadowPower() const
{
	if (_type == LightType::Spot)
		return _spotLight->shadowPower;

	return 0; // think about default value
}

glm::float_t LightInterface::getIntensity() const
{
	switch (_type)
	{
	case Directional:
		return _directLight->intensity;
	case Point:
		return _pointLight->intensity;
	case Spot:
		return _spotLight->intensity;
	default:
		return 0; // think about default value
	}
}

void LightInterface::setLightStruct(DirectLight *directLight)
{
	_type = Directional;
	_directLight = directLight;
}

void LightInterface::setLightStruct(PointLight *pointLight)
{
	_type = Point;
	_pointLight = pointLight;
}

void LightInterface::setLightStruct(SpotLight *spotLight)
{
	_type = Spot;
	_spotLight = spotLight;
}

void LightInterface::setColor(glm::vec4 color)
{
	switch (_type)
	{
	case Directional:
		_directLight->color = color;
		break;
	case Point:
		_pointLight->color = color;
		break;
	case Spot:
		_spotLight->color = color;
		break;
	default: //may should write log ?
		break;
	}
}

void LightInterface::setDirection(glm::vec4 direction)
{
	switch (_type)
	{
	case Directional:
		_directLight->direction = direction;
		break;
	case Spot:
		_spotLight->direction = direction;
		break;
	default: //may should write log ?
		break;
	}
}

void LightInterface::setAngle(glm::float_t angle)
{
	if (_type == Spot)
		_spotLight->angle = angle;
}

void LightInterface::setShadowPower(glm::float_t shadowPower)
{
	if (_type == Spot)
		_spotLight->shadowPower = shadowPower;

}

void LightInterface::setIntensity(glm::float_t intensity)
{
	switch (_type)
	{
	case Directional:
		_directLight->intensity = intensity;
		break;
	case Point:
		_pointLight->intensity = intensity;
		break;
	case Spot:
		_spotLight->intensity = intensity;
		break;
	default: //may should write log ?
		break;
	}
}

void LightInterface::setPosition(glm::vec4 pos)
{
	switch (_type)
	{
	case Point:
		_pointLight->position = pos;
		break;
	case Spot:
		_spotLight->position = pos;
		break;
	default: //may should write log ?
		break;
	}
}