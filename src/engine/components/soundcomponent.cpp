#include "soundcomponent.h"
SoundComponent::SoundComponent() :soundSource(nullptr)
{
}

SoundComponent::~SoundComponent()
{
}

void SoundComponent::setSoundSource(SoundSource *soundSource)
{
	this->soundSource = soundSource;
}

void SoundComponent::setPos(float x, float y, float z)
{
	this->soundSource->setPos(x, y, z);
}

FMOD_VECTOR SoundComponent::getPos()
{
	return this->soundSource->getPos();
}

FMOD::Sound* SoundComponent::getSound()
{
	return this->soundSource->getSound();
}