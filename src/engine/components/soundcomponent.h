#ifndef SOUND_H
#define SOUND_H

#include "../global.h"
#include <entityx/Entity.h>
#include  <fmod/fmod.hpp>
#include "../meta/object.h"
#include "../soundsource.h"

class ENGINE_EXPORT SoundComponent :
	public entityx::Component<SoundComponent>,
	public Object
{
public:
	SoundComponent();
	~SoundComponent();
	SoundSource *soundSource;
	void setSoundSource(SoundSource *soundSource);
	void setPos(float x, float y, float z);
	FMOD_VECTOR getPos();
	FMOD::Sound* getSound();
};
#endif