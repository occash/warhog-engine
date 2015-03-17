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
	void setSoundSource(SoundSource *soundSource);
	SoundSource *soundSource;
};
#endif