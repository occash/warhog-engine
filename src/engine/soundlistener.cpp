#include "soundlistener.h"
SoundListener::SoundListener()
{
    _pos = { 0.0f, 0.0f, 0.0f};
    _forward = { 0.0f, 0.0f, -1.0f };//vector length  must be 1
    _up = {0.0f, 1.0f, 0.0f};//vector length  must be 1
}

SoundListener::~SoundListener()
{
}

void SoundListener::setPos(float x, float y, float z)
{
    _pos = { x, y, z};
}
void SoundListener::setForward(float x, float y, float z)
{
    glm::vec3 forward = { x, y, z };
    glm::vec3 forward_normalized = glm::normalize(forward);
    _forward = forward;
}
void SoundListener::setUp(float x, float y, float z)
{
    glm::vec3 up = { x, y, z };
    glm::vec3 up_normalized = glm::normalize(up);
    _up = up;
}


void SoundListener::setPos(const glm::vec3& pos)
{
    _pos = pos;
}

void SoundListener::setForward(const glm::vec3& forward)
{
    glm::vec3 forward_normalized = glm::normalize(forward);
    _forward = forward_normalized;
}


void SoundListener::setUp(const glm::vec3& up)
{
    glm::vec3 up_normalized = glm::normalize(up);
    _up = up_normalized;
}

glm::vec3 SoundListener::getPos()
{
    return _pos;
}

glm::vec3 SoundListener::getForward()
{
    return _forward;
}


glm::vec3 SoundListener::getUp()
{
    return _up;
}