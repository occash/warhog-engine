#ifndef WINDOW_H
#define WINDOW_H

#include "global.h"
#include "flags.h"
#include <string>

class NativeWindow;

class ENGINE_EXPORT Window
{
public:
    enum Style
    {
        Clozable = 1 << 0,
        Resizable = 1 << 1,
        PreventSaver = 1 << 2
    };

    enum State
    {
        Normal = 1 << 0,
        Mimimized = 1 << 1,
        Maximized = 1 << 2,
        Fullsceren = 1 << 3,
        Active = 1 << 4
    };

    W_DECLAGE_FLAGS(Styles, Style)
    W_DECLAGE_FLAGS(States, State)

public:
    Window();
    ~Window();

    bool isVisible() const;
    void show();
    void showNormal();
    void hide();
    bool isFullscreen() const;
    void showFullscreen();
    bool isMinimized() const;
    void showMinimized();
    bool isMaximized() const;
    void showMaximized();
    void close();

    int x() const;
    int y() const;
    int width() const;
    int height() const;
    void move(int x, int y);
    void resize(int w, int h);

    std::string title() const;
    void setTitle(const std::string& title);

    bool isActiveWindow() const;
    void activateWindow();

    bool isMouseGrabbed() const;
    void grabMouse();
    void releaseMouse();

    bool isCursorVisible() const;
    void showCursor();
    void hideCursor();

    /*  static bool platformEvent(Window *, void *, long *);

        protected:
        virtual void create();
        virtual void destroy();
        virtual void closeEvent();
        virtual void moveEvent(int x, int y);
        virtual void resizeEvent(int w, int h);
        virtual void focusInEvent();
        virtual void focusOutEvent();
        virtual void showEvent();
        virtual void hideEvent();
        virtual void updateEvent();*/

private:
    friend class Context;
    friend class Input;
    NativeWindow *_window;

};

#endif