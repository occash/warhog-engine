#ifndef NATIVEWINDOW_H
#define NATIVEWINDOW_H

#include "global.h"
#include "window.h"

class NativeInput;

class NativeWindow
{
public:
    virtual void create() = 0;
    virtual void destroy() = 0;

    virtual bool isVisible() const = 0;
    virtual void setVisible(bool) = 0;

    virtual Window::States states() = 0;
    virtual void setStates(Window::States) = 0;

    virtual int x() const = 0;
    virtual int y() const = 0;
    virtual void move(int, int) = 0;

    virtual int width() const = 0;
    virtual int height() const = 0;
    virtual void resize(int, int) = 0;

    virtual const char *title() const = 0;
    virtual void setTitle(const char *) = 0;

    virtual bool isMouseGrabbed() const = 0;
    virtual void setMouseGrab(bool) = 0;

    virtual bool isCursorVisible() const = 0;
    virtual void setCursorVisible(bool visible) = 0;

    virtual void setupInput(NativeInput *) = 0;

    virtual void *handle() const = 0;

};

#endif //NATIVEWINDOW_H
