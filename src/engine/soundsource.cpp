#include "soundsource.h"


SoundSource::SoundSource()
{
}

SoundSource::~SoundSource()
{
}

void SoundSource::setFileName(char *fileName)
{
    _fileName = fileName;
}

void SoundSource::setSound(FMOD::Sound *sound)
{
    _sound = sound;
}

void SoundSource::setChannel(FMOD::Channel *channel)
{
    _channel = channel;
}

void SoundSource::setPos(float x, float y, float z)
{
    _pos = {x, y, z};
}

void SoundSource::setPos(const glm::vec3& pos)
{
    //_pos = { -pos.x, pos.y, pos.z };
    _pos = pos;
}

glm::vec3 SoundSource::getPos()
{
    return _pos;
}

FMOD::Sound *SoundSource::getSound()
{
    return _sound;
}

FMOD::Channel *SoundSource::getChannel()
{
    return _channel;
}

void SoundSource::setMinDistance(float minDistance)
{
    _minDistance = minDistance;
}

float SoundSource::getMinDistance()
{
    return _minDistance;
}

char *SoundSource::getFileName()
{
    return _fileName;
}

void SoundSource::play()
{
    _isPlaying = true;
}

void SoundSource::stop()
{
    _isPlaying = false;
}

bool SoundSource::isPlaying()
{
    return _isPlaying;
}

void SoundSource::changeLoopMode(bool islooping)
{
    _isLooping = islooping;
}

bool SoundSource::isLooping()
{
    return _isLooping;
}