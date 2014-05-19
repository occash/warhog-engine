#ifndef INPUT_H
#define INPUT_H

#include <list>
#include <map>

#include <glm/glm.hpp>

#include "global.h"

class Window;
class GLFWwindow;

class Input
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

    typedef std::map<std::string, int> KeyMap;

public:
    static bool key(const std::string& name);
    static bool button(Button b);
    static glm::float_t axis(Axis a);

private:
    friend class InputSystem;

    static Ptr<Window> _window;
    static KeyMap _keyMap;
    static double _deltah;
    static double _deltav;

};

#endif
