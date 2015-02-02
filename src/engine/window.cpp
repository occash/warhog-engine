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
	_window->destroy();
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

void Window::showFullscreen()
{
	_window->setVisible(true);
	_window->setFullscreen(true);
}

void Window::hide()
{
	_window->setVisible(false);
}

void Window::close()
{
	_window->close();
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