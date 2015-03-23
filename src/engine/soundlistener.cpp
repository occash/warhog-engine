#include "soundlistener.h"
SoundListener::SoundListener()
{
	pos = { 0.0f, 0.0f, 0.0f };
	forward = { 0.0f, 1.0f, 0.0f};//vector length  must be 1 
	up = { 0.0f, 0.0f, 0.0f};//vector length  must be 1 
}

SoundListener::~SoundListener()
{
}

void SoundListener::setPos(float x, float y, float z)
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
}
void SoundListener::setForward(float x, float y, float z)
{
	forward.x = x;
	forward.y = y;
	forward.z = z;
}
void SoundListener::setUp(float x, float y, float z)
{
	up.x = x;
	up.y = y;
	up.z = z;
}

FMOD_VECTOR SoundListener::getPos()
{
	return pos;
}

FMOD_VECTOR SoundListener::getForward()
{
	return forward;
}

FMOD_VECTOR SoundListener::getUp()
{
	return up;
}