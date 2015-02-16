#include "window.h"
#include "platformmanager.h"
#include "nativewindow.h"

Window::Window()
    : _window(PlatformManager::instance()->window())
{
    _window->create();
}

Window::~Window()
{
    releaseMouse();
    close();
    delete _window;
}

bool Window::isVisible() const
{
    return _window->isVisible();
}

void Window::show()
{
    _window->setVisible(true);
}

void Window::showNormal()
{
    _window->setStates(Active);
    _window->setVisible(true);
}

void Window::showFullscreen()
{
    _window->setStates(Active | Fullsceren);
    _window->setVisible(true);
}

bool Window::isMinimized() const
{
    return _window->states() & Mimimized;
}

void Window::showMinimized()
{
    _window->setStates(Active | Mimimized);
    _window->setVisible(true);
}

bool Window::isMaximized() const
{
    return _window->states() & Maximized;
}

void Window::showMaximized()
{
    _window->setStates(Active | Maximized);
    _window->setVisible(true);
}

void Window::hide()
{
    _window->setVisible(false);
}

bool Window::isFullscreen() const
{
    return _window->states() & Fullsceren;
}

void Window::close()
{
    _window->setVisible(false);
    _window->destroy();
}

int Window::x() const
{
    return _window->x();
}

int Window::y() const
{
    return _window->y();
}

int Window::width() const
{
    return _window->width();
}

int Window::height() const
{
    return _window->height();
}

void Window::move(int x, int y)
{
    _window->move(x, y);
}

void Window::resize(int w, int h)
{
    _window->resize(w, h);
}

std::string Window::title() const
{
    return _window->title();
}

void Window::setTitle(const std::string& title)
{
    _window->setTitle(title.c_str());
}

bool Window::isActiveWindow() const
{
    return _window->states() & Active;
}

void Window::activateWindow()
{
    _window->setStates(_window->states() | Active);
    _window->setVisible(true);
}

bool Window::isMouseGrabbed() const
{
    return _window->isMouseGrabbed();
}

void Window::grabMouse()
{
    _window->setMouseGrab(true);
}

void Window::releaseMouse()
{
    _window->setMouseGrab(false);
}

bool Window::isCursorVisible() const
{
    return _window->isCursorVisible();
}

void Window::showCursor()
{
    _window->setCursorVisible(true);
}

void Window::hideCursor()
{
    _window->setCursorVisible(false);
}

void *Window::handle() const
{
    return _window->handle();
}