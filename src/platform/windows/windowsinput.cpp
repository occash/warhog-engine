#include "windowsinput.h"
#include "windowswindow.h"

#include <bitset>

struct InputData
{
    struct Mouse
    {
        int x = 0, y = 0;
        int button = 0;
    } mouse;

    struct Keyboard
    {
        std::bitset<Input::NumKeys> keys;
    } keyboard;
};

WindowsInput::WindowsInput()
    : _data(new InputData)
{
}

WindowsInput::~WindowsInput()
{
    delete _data;
}

bool WindowsInput::key(unsigned int key) const
{
    if (key < 0 || key > Input::NumKeys)
        return false;

    return _data->keyboard.keys.test(key);
}

bool WindowsInput::button(Input::Button b) const
{
    return _data->mouse.button & (1 << b);
}

float WindowsInput::axis(Input::Axis a) const
{
    return 0.0;
}

float WindowsInput::mouseX() const
{
    return _data->mouse.x;
}

float WindowsInput::mouseY() const
{
    return _data->mouse.y;
}

void WindowsInput::keyDown(unsigned int key)
{
    _data->keyboard.keys.set(key, true);
}

void WindowsInput::keyUp(unsigned int key)
{
    _data->keyboard.keys.set(key, false);
}

void WindowsInput::mouseMove(int x, int y)
{
    _data->mouse.x = x;
    _data->mouse.y = y;
}

void WindowsInput::buttonDown(Input::Button b)
{
    _data->mouse.button |= (1 << b);
}

void WindowsInput::buttonUp(Input::Button b)
{
    _data->mouse.button &= ~(1 << b);
}
