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
private:
    SoundListener *_listener;
public:
    ListenerComponent();
    ~ListenerComponent();

    void setSoundListener(SoundListener *listener);
    SoundListener *getSoundListener();
    void setPos(float x, float y, float z);
    void setForward(float x, float y, float z);
    void setUp(float x, float y, float z);
    void setPos(const glm::vec3& pos);
    void setForward(const glm::vec3& forward);
    void setUp(const glm::vec3& up);

    glm::vec3 getPos();
    glm::vec3 getForward();
    glm::vec3 getUp();
};
#endif