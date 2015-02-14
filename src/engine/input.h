#ifndef INPUT_H
#define INPUT_H

#include "global.h"

#include <string>
#include <map>
#include <memory>

class Window;

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
	enum Keys
	{
		KEY_ESC = 256,
		KEY_TAB,
		KEY_BACKSPACE,
		KEY_RETURN,
		KEY_DELETE,
		KEY_INSERT,
		KEY_HOME,
		KEY_END,
		KEY_PGUP,
		KEY_PGDOWN,
		KEY_LEFT,
		KEY_RIGHT,
		KEY_UP,
		KEY_DOWN,
		KEY_SHIFT,
		KEY_CTRL,
		KEY_ALT,
		KEY_SCROLL,
		KEY_CAPS,
		KEY_NUM,
		KEY_F1,
		KEY_F2,
		KEY_F3,
		KEY_F4,
		KEY_F5,
		KEY_F6,
		KEY_F7,
		KEY_F8,
		KEY_F9,
		KEY_F10,
		KEY_F11,
		KEY_F12,
		NUM_KEYS
	};

    typedef std::map<std::string, int> KeyMap;

public:
    static bool key(const std::string& name);
    static bool button(Button b);
    static float axis(Axis a);

private:
    friend class InputSystem;

    static std::shared_ptr<Window> _window;
    static KeyMap _keyMap;
    static double _deltah;
	static double _deltav;

};

#endif
