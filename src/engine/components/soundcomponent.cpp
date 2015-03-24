#include "soundcomponent.h"
SoundComponent::SoundComponent() : _soundSource(nullptr)
{
}

SoundComponent::~SoundComponent()
{
}

void SoundComponent::setSoundSource(SoundSource *soundSource, float distanceFactor)
{
    _soundSource = soundSource;
}

void SoundComponent::setPos(float x, float y, float z)
{
    _soundSource->setPos(x, y, z);
}

glm::vec3 SoundComponent::getPos()
{
    return _soundSource->getPos();
}

void SoundComponent::setPos(const glm::vec3& pos)
{
	_soundSource->setPos(pos);
}


SoundSource* SoundComponent::getSoundSource()
{
	return _soundSource;
}
