#include "input.h"
#include "window.h"

//#include <GLFW/glfw3.h>
#include <iostream>

bool Input::key(const std::string& name)
{
    //return glfwGetKey(_window->_handle, _keyMap.at(name)) == GLFW_PRESS;
    return false;
}

float Input::axis(Axis a)
{
    switch (a)
    {
    case Input::Horizontal:
        return _deltah;
    case Input::Vertical:
        return _deltav;
    default:
        return 0.0;
    }
}

bool Input::button(Button b)
{
    //return glfwGetMouseButton(_window->_handle, b) == GLFW_PRESS;
    return false;
}

double Input::_deltav = 0.0;
double Input::_deltah = 0.0;
Input::KeyMap Input::_keyMap;
std::shared_ptr<Window> Input::_window;
