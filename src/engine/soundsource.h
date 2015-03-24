#ifndef SOUNDSOURCE_H
#define SOUNDSOURCE_H
#include <glm/glm.hpp>

namespace FMOD
{
	class Sound;
	class Channel;
}

class SoundSource 
{
	
private:
	FMOD::Sound *_sound;
	FMOD::Channel   *_channel = 0;//using, when sound is playing
	glm::vec3 _pos;
	float _minDistance = 1.0f;
	float _maxDistance = 10.0f;
public:
    SoundSource();
    ~SoundSource();
    void setSound(FMOD::Sound *sound);
    void setChannel(FMOD::Channel *channel);
    void setPos(float x, float y, float z);
	void setPos(const glm::vec3& pos);
	void setMinDistance(float minDistance);
	void setMaxDistance(float maxDistance);
	float getMinDistance();
	float getMaxDistance();
	glm::vec3 getPos();
    FMOD::Sound* getSound();
	FMOD::Channel* getChannel();
    //TODO:change LoopMode
    //TODO: Play control:volume, start, stop
};
#endif