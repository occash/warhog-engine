#ifndef SOUNDLISTENER_H
#define SOUNDLISTENER_H
#include  <fmod/fmod.hpp>
class SoundListener //приемник звука
{
public:
	FMOD_RESULT result;//для хранения кодов ошибок
	SoundListener();
	~SoundListener();
};
#endif