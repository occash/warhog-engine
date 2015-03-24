#include "listenercomponent.h"
ListenerComponent::ListenerComponent()
{
}

ListenerComponent::~ListenerComponent()
{
}

void ListenerComponent::setSoundListener(SoundListener *listener)
{	
    _listener = listener;
}

SoundListener* ListenerComponent::getSoundListener()
{
	return _listener;
}

void ListenerComponent::setPos(float x, float y, float z)
{
    _listener->setPos(x, y, z);
}
void ListenerComponent::setForward(float x, float y, float z)
{
    _listener->setForward(x, y, z);
}
void ListenerComponent::setUp(float x, float y, float z)
{
    _listener->setUp(x, y, z);
}

void ListenerComponent::setPos(const glm::vec3& pos)
{
	_listener->setPos(pos);
}
void ListenerComponent::setForward(const glm::vec3& forward)
{
	_listener->setForward(forward);
}
void ListenerComponent::setUp(const glm::vec3& up)
{
	_listener->setUp(up);
}



glm::vec3 ListenerComponent::getPos()
{
    return _listener->getPos();
}

glm::vec3 ListenerComponent::getForward()
{
    return _listener->getForward();
}

glm::vec3 ListenerComponent::getUp()
{
    return _listener->getUp();
}