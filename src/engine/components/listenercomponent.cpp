#include "listenercomponent.h"
ListenerComponent::ListenerComponent()
{
}

ListenerComponent::~ListenerComponent()
{
}

void ListenerComponent::setSoundListener(SoundListener *listener)
{
	this->listener = listener;
}

void ListenerComponent::setPos(float x, float y, float z)
{
	this->listener->setPos(x, y, z);
}
void ListenerComponent::setForward(float x, float y, float z)
{
	this->listener->setForward(x, y, z);
}
void ListenerComponent::setUp(float x, float y, float z)
{
	this->listener->setUp(x, y, z);
}

FMOD_VECTOR ListenerComponent::getPos()
{
	return this->listener->getPos();
}

FMOD_VECTOR ListenerComponent::getForward()
{
	return this->listener->getForward();
}

FMOD_VECTOR ListenerComponent::getUp()
{
	return this->listener->getUp();
}