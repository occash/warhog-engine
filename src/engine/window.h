#ifndef WINDOW_H
#define WINDOW_H

#include "global.h"
#include "hints.h"

struct GLFWwindow;

class CameraComponent;
class Model;

class ENGINE_EXPORT Window
{
public:
    Window(const GLWindowHints& hints = GLWindowHints(), 
        Ptr<Window> share = nullptr);
    virtual ~Window();

    void render();
    bool isClosing() const;
    unsigned int handle() const;
    int width() const;
    int height() const;

	void show();
	void hide();
	void setResizable(bool arg);
	void setDecorated(bool arg);

private:
    void setWindow(const GLWindowHints& hints);

private:
    friend class GLContext;
    friend class Input;
    friend class InputSystem;

    GLWindowHints _hints;
    GLFWwindow *_handle;

};

#endif