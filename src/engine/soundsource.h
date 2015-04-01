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
	char* _fileName = "";
	bool _isPlaying = false;
	bool _isLooping = false;
public:
    SoundSource();
    ~SoundSource();
	void play();
	void stop();
	

    void setSound(FMOD::Sound *sound);
    void setChannel(FMOD::Channel *channel);
    void setPos(float x, float y, float z);
    void setPos(const glm::vec3& pos);
    void setMinDistance(float minDistance);
	void setFileName(char* fileName);
	void changeLoopMode(bool islooping);
	
	bool isLooping();
	bool isPlaying();
	char* getFileName();
    float getMinDistance();
    glm::vec3 getPos();
    FMOD::Sound *getSound();
    FMOD::Channel *getChannel();
    //TODO: Play control:volume
};
#endif