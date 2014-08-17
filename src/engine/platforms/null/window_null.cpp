#include "window.h"

Window::Window(int style) :
	_data(nullptr)
{
}

Window::~Window()
{
}

int Window::x() const
{
}

int Window::y() const
{
}

int Window::width() const
{
}

int Window::height() const
{
}

void Window::setPosition(int x, int y)
{
}

void Window::setSize(int w, int h)
{
}

void Window::setTitle(const char *title)
{
}

void Window::setVisible(bool v)
{
}

void Window::show()
{
}

void Window::hide()
{
}

void Window::showFullscreen()
{
}

void Window::close()
{
}

void Window::update()
{
}

void Window::event(Window::Event e)
{
}

void Window::create(void *data)
{
}

void Window::destroy(void *data)
{
}

void Window::moveEvent()
{
}

void Window::resizeEvent()
{
}

void Window::closeEvent()
{
}

void Window::visibleEvent()
{
}
