#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include "../global.h"
#include "../window.h"

#include <entityx\System.h>
#include <string>
#include <map>

typedef std::map<std::string, int> KeyMap;

class InputSystem : public entityx::System<InputSystem>
{
public:
    InputSystem(std::shared_ptr<Window> window, const KeyMap& keyMap);
    ~InputSystem();

    void configure(entityx::EventManager& events) override;
    void update(entityx::EntityManager& entities, entityx::EventManager& events, double dt) override;

private:
    double _horizontal;
    double _vertical;

};

#endif
