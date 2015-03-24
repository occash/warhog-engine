#include "soundsource.h"


SoundSource::SoundSource()
{
}

SoundSource::~SoundSource()
{
}

void SoundSource::setSound(FMOD::Sound *sound)
{
    _sound = sound;
}

void SoundSource::setChannel(FMOD::Channel *channel)
{
    _channel = channel;
}

void SoundSource::setPos(float x, float y, float z)
{
	_pos.x = { x, y, z };
}

void SoundSource::setPos(const glm::vec3& pos)
{
	_pos = pos;
}

glm::vec3 SoundSource::getPos()
{
	return _pos;
}

FMOD::Sound* SoundSource::getSound()
{
    return _sound;
}

FMOD::Channel* SoundSource::getChannel()
{
	return _channel;
}

void SoundSource::setMinDistance(float minDistance)
{
	_minDistance = minDistance;
}
void SoundSource::setMaxDistance(float maxDistance)
{
	_maxDistance = maxDistance;
}
float SoundSource::getMinDistance()
{
	return _minDistance;
}
float SoundSource::getMaxDistance()
{
	return _maxDistance;
}
