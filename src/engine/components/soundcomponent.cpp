#include "soundcomponent.h"
SoundComponent::SoundComponent() : _soundSource(nullptr)
{
}

SoundComponent::~SoundComponent()
{
}

void SoundComponent::setSoundSource(SoundSource *soundSource)
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


SoundSource *SoundComponent::getSoundSource()
{
    return _soundSource;
}

void SoundComponent::play()
{
	_soundSource->play();
}

void SoundComponent::stop()
{
	_soundSource->stop();
}

bool SoundComponent::isPlaying()
{
	return _soundSource->isPlaying();
}

void SoundComponent::changeLoopMode(bool isLooping)
{
	_soundSource->changeLoopMode(isLooping);
}

bool SoundComponent::isLooping()
{
	return _soundSource->isLooping();
}