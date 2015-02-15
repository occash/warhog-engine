#ifndef WINDOWSWINDOW_H
#define WINDOWSWINDOW_H

#include <nativewindow.h>

class WindowsWindow : public NativeWindow
{
public:
    WindowsWindow();
    ~WindowsWindow();

    void create() override;
    void destroy() override;

    bool isVisible() const override;
    void setVisible(bool visible) override;

    NativeWindow::States states() override;
    void setStates(NativeWindow::States) override;

    int x() const override;
    int y() const override;
    void move(int x, int y) override;

    int width() const override;
    int height() const override;
    void resize(int w, int h) override;

    const char *title() const override;
    void setTitle(const char *title) override;

    bool isMouseGrabbed() const override;
    void setMouseGrab(bool) override;

    bool isCursorVisible() const override;
    void setCursorVisible(bool visible) override;

public:
    void *handle() const;

    static bool platformEvent(WindowsWindow *window, void *msgPtr, long *result);

private:
    friend struct WindowData;
    WindowData *_data;

};

#endif //WINDOWSWINDOW_H
