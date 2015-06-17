#include "lightinterface.h"
#include "systems/rendersystem.h"

#define asPointLight(x) reinterpret_cast<PointLight*>(x)
#define asDirectLight(x) reinterpret_cast<DirectLight*>(x)
#define asSpotLight(x) reinterpret_cast<SpotLight*>(x)

LightInterface::LightInterface(RenderSystem *renderSystem) : _renderSys(renderSystem)
{

}

void LightInterface::setType(LightType type)
{
	_light = _renderSys->getStucture(type);
	_type = type;
}

glm::vec4 LightInterface::getPosition() const
{
	switch (_type)
	{
	case Point:
		return asPointLight(_light)->position;
	case Spot:
		return asSpotLight(_light)->position;
	default:
		return glm::vec4{0, 0, 0, 0 }; // think about default value
	}
}

glm::vec4 LightInterface::getColor() const
{
	switch (_type)
	{
	case Directional:
		return asSpotLight(_light)->color;
	case Point:
		return asPointLight(_light)->color;
	case Spot:
		return asSpotLight(_light)->color;
	default:
		return glm::vec4{ 0, 0, 0, 0 }; // think about default value
	}
}

glm::vec4 LightInterface::getDirection() const
{
	switch (_type)
	{
	case Directional:
		return asSpotLight(_light)->direction;
	case Spot:
		return asSpotLight(_light)->direction;
	default:
		return glm::vec4{0, 0, 0, 0}; // think about default value
	}
}

glm::float_t LightInterface::getAngle() const
{
	if (_type == LightType::Spot)
		return asSpotLight(_light)->angle;

	return 0; // think about default value
}

glm::float_t LightInterface::getShadowPower() const
{
	if (_type == LightType::Spot)
		return asSpotLight(_light)->shadowPower;

	return 0; // think about default value
}

glm::float_t LightInterface::getIntensity() const
{
	switch (_type)
	{
	case Directional:
		return asSpotLight(_light)->intensity;
	case Point:
		return asPointLight(_light)->intensity;
	case Spot:
		return asSpotLight(_light)->intensity;
	default:
		return 0; // think about default value
	}
}


void LightInterface::setColor(glm::vec4 color)
{
	switch (_type)
	{
	case Directional:
		asSpotLight(_light)->color = color;
		break;
	case Point:
		asPointLight(_light)->color = color;
		break;
	case Spot:
		asSpotLight(_light)->color = color;
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
		asSpotLight(_light)->direction = direction;
		break;
	case Spot:
		asSpotLight(_light)->direction = direction;
		break;
	default: //may should write log ?
		break;
	}
}

void LightInterface::setAngle(glm::float_t angle)
{
	if (_type == Spot)
		asSpotLight(_light)->angle = angle;
}

void LightInterface::setShadowPower(glm::float_t shadowPower)
{
	if (_type == Spot)
		asSpotLight(_light)->shadowPower = shadowPower;

}

void LightInterface::setIntensity(glm::float_t intensity)
{
	switch (_type)
	{
	case Directional:
		asSpotLight(_light)->intensity = intensity;
		break;
	case Point:
		asPointLight(_light)->intensity = intensity;
		break;
	case Spot:
		asSpotLight(_light)->intensity = intensity;
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
		asPointLight(_light)->position = pos;
		break;
	case Spot:
		asSpotLight(_light)->position = pos;
		break;
	default: //may should write log ?
		break;
	}
}