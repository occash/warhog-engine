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
	void play();
	void stop();
	void changeLoopMode(bool isLooping);

    void setSoundSource(SoundSource *soundSource);
    void setPos(float x, float y, float z);
    void setPos(const glm::vec3& pos);

	SoundSource *getSoundSource();
    glm::vec3 getPos();
	bool isPlaying();
	bool isLooping();
};
#endif