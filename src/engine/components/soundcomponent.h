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
private:
	SoundSource *_soundSource;
public:
    SoundComponent();
    ~SoundComponent();
	SoundSource* getSoundSource();
	void setSoundSource(SoundSource *soundSource,float distanceFactor=1.0f);
    void setPos(float x, float y, float z);
	void setPos(const glm::vec3& pos);
	glm::vec3 getPos();
};
#endif