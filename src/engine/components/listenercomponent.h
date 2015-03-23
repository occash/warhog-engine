#ifndef LISTENER_H
#define LISTENER_H

#include "../global.h"
#include <entityx/Entity.h>
#include "../meta/object.h"
#include "../soundlistener.h"

class ENGINE_EXPORT ListenerComponent :
	public entityx::Component<ListenerComponent>,
	public Object
{
public:
	ListenerComponent();
	~ListenerComponent();
	SoundListener* listener;
	void setSoundListener(SoundListener *listener);
	void setPos(float x, float y, float z);
	void setForward(float x, float y, float z);
	void setUp(float x, float y, float z);
	FMOD_VECTOR getPos();
	FMOD_VECTOR getForward();
	FMOD_VECTOR getUp();
};
#endif