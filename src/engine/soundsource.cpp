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