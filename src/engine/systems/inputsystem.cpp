#include "inputsystem.h"
#include "../input.h"
#include "../window.h"

#include <GLFW/glfw3.h>


InputSystem::InputSystem(Ptr<Window> window, const KeyMap& keys)
{
    Input::_window = window;
    Input::_keyMap = keys;
}


InputSystem::~InputSystem()
{
}

void InputSystem::configure(EventManager &events)
{

}

void InputSystem::update(EntityManager &entities, EventManager &events, double dt)
{
    double horizontal, vertical;
    glfwGetCursorPos(Input::_window->_handle,
        &horizontal,
        &vertical);

    Input::_deltah = horizontal - _horizontal;
    Input::_deltav = vertical - _vertical;
    _horizontal = horizontal;
    _vertical = vertical;
}
