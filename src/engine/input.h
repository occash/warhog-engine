#ifndef INPUT_H
#define INPUT_H

#include "global.h"

#include <string>

class Window;
class NativeInput;

class ENGINE_EXPORT Input
{
public:
    enum Axis
    {
        Horizontal,
        Vertical
    };
    enum Button
    {
        Left,
        Middle,
        Right,
        Special1,
        Special2,
        Special3,
        Special4,
        Special5,
    };
    enum Keys
    {
        KeyEsc = 256,
        KeyTab,
        KeyBackspace,
        KeyReturn,
        KeyDelete,
        KeyInsert,
        KeyHome,
        KeyEnd,
        KeyPgup,
        KeyPgdown,
        KeyLeft,
        KeyRight,
        KeyUp,
        KeyDown,
        KeyShift,
        KeyCtrl,
        KeyAlt,
        KeyScroll,
        KeyCaps,
        KeyNum,
        KeyF1,
        KeyF2,
        KeyF3,
        KeyF4,
        KeyF5,
        KeyF6,
        KeyF7,
        KeyF8,
        KeyF9,
        KeyF10,
        KeyF11,
        KeyF12,
        NumKeys
    };

public:
    Input(Window *);
    ~Input();

    bool key(const std::string& name) const;
    bool button(Button b) const;
    float axis(Axis a) const;
    float mouseX() const;
    float mouseY() const;

private:
    NativeInput *_input;

};

#endif
