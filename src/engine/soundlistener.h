#ifndef SOUNDLISTENER_H
#define SOUNDLISTENER_H
#include  <fmod/fmod.hpp>
class SoundListener //приемник звука
{
public:
	FMOD_RESULT result;//для хранения кодов ошибок
	SoundListener();
	~SoundListener();
	FMOD_VECTOR pos;
	FMOD_VECTOR forward;
	FMOD_VECTOR up;
	void setPos(float x, float y, float z);
	void setForward(float x, float y, float z);
	void setUp(float x, float y, float z);
	FMOD_VECTOR getPos();
	FMOD_VECTOR getForward();
	FMOD_VECTOR getUp();
};
#endif