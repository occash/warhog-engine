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