#ifndef SOUNDLISTENER_H
#define SOUNDLISTENER_H
#include  <fmod/fmod.hpp>
class SoundListener //�������� �����
{
public:
	FMOD_RESULT result;//��� �������� ����� ������
	SoundListener();
	~SoundListener();
};
#endif