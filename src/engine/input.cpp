#include "input.h"
#include "platformmanager.h"
#include "nativeinput.h"
#include "nativewindow.h"

Input::Input(Window *window)
    : _input(PlatformManager::instance()->input())
{
    window->_window->setupInput(_input);
}

Input::~Input()
{
    delete _input;
}

bool Input::key(const std::string& name) const
{
    //TODO: InputManager
    return _input->key('w');
}

float Input::axis(Axis a) const
{
    return _input->axis(a);
}

bool Input::button(Button b) const
{
    return _input->button(b);
}

float Input::mouseX() const
{
    return _input->mouseX();
}

float Input::mouseY() const
{
    return _input->mouseY();
}
