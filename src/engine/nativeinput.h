#ifndef NATIVEINPUT_H
#define NATIVEINPUT_H

#include "input.h"

class NativeInput
{
public:
    virtual bool key(unsigned int key) const = 0;
    virtual bool button(Input::Button b) const = 0;
    virtual float axis(Input::Axis a) const = 0;
    virtual float mouseX() const = 0;
    virtual float mouseY() const = 0;

};

#endif //NATIVEINPUT_H