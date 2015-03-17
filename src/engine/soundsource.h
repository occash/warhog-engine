#ifndef SOUNDSOURCE_H
#define SOUNDSOURCE_H
#include <fmod/fmod.hpp>
class SoundSource //источник звука
{
public:
	SoundSource();
	~SoundSource();
	FMOD::Sound *sound;
	FMOD::Channel   *channel = 0;//using, when sound is playing
	bool playing = false;
	float minDistance = 100.0f;
	float maxDistance = 100000.0f;
	void setSound(FMOD::Sound* sound);
	void setChannel(FMOD::Channel* channel);
	//TODO:LoopMode
	//TODO: Play control:volume, start, stop
};
#endif