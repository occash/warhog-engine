#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include <entityx\System.h>
#include <string>

#include "../global.h"
#include "../window.h"

using namespace entityx;

typedef std::map<std::string, int> KeyMap;

class InputSystem : public System<InputSystem>
{
public:
    InputSystem(Ptr<Window> window, const KeyMap& keyMap);
    ~InputSystem();

    void configure(ptr<EventManager> events);
    void update(ptr<EntityManager> entities, ptr<EventManager> events, double dt) override;

private:
    double _horizontal;
    double _vertical;

};

#endif
