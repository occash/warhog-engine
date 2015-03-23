#include "soundsource.h"


SoundSource::SoundSource()
{
}

SoundSource::~SoundSource()
{
}

void SoundSource::setSound(FMOD::Sound* sound)
{
	this->sound = sound;
}

void SoundSource::setChannel(FMOD::Channel* channel)
{
	this->channel = channel;
}

void SoundSource::setPos(float x, float y, float z)
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

FMOD_VECTOR SoundSource::getPos()
{
	return pos;
}

FMOD::Sound* SoundSource::getSound()
{
	return sound;
}