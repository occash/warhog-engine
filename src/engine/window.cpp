#include "window.h"
#include "monitor.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <iostream>

/*struct WindowData
{
    unsigned int handle;
    int width;
    int height;
    int flags;
    bool minimized;
    bool focused;
};*/

void resizeEvent(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Window::Window(const GLWindowHints& hints, Ptr<Window> share)
{
    _hints = hints;
    setWindow(hints);

    _handle = glfwCreateWindow(
        hints.width, 
        hints.height, 
        hints.title.c_str(),
        hints.fullscreen ?
        Monitor::screen(hints.monitor)->_handle
        : nullptr, 
        share.get() ? share->_handle : nullptr
        );

    glfwSetWindowSizeCallback(_handle, resizeEvent);
}

Window::~Window(void)
{
    glfwDestroyWindow(_handle);
}

void Window::setWindow(const GLWindowHints& hints)
{
    glfwWindowHint(GLFW_VISIBLE, hints.visible ? GL_TRUE : GL_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, hints.resizable ? GL_TRUE : GL_FALSE);
    glfwWindowHint(GLFW_DECORATED, hints.decorated ? GL_TRUE : GL_FALSE);
}

void Window::render()
{
    glfwSwapBuffers(_handle);
    glfwPollEvents();
}

bool Window::isClosing() const
{
    return glfwWindowShouldClose(_handle);
}

unsigned int Window::handle() const
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    return (unsigned int)glfwGetWin32Window(_handle);
#else
    return 0;
#endif
}

int Window::width() const
{
    int width;
    glfwGetWindowSize(_handle, &width, nullptr);
    return width;
}

int Window::height() const
{
    int height;
    glfwGetWindowSize(_handle, nullptr, &height);
    return height;
}

void Window::show()
{
	glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
}

void Window::hide()
{
	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
}

void Window::setResizable(bool arg)
{
	glfwWindowHint(GLFW_RESIZABLE, arg ? GL_TRUE : GL_FALSE);
}

void Window::setDecorated(bool arg)
{
	glfwWindowHint(GLFW_DECORATED, arg ? GL_TRUE : GL_FALSE);
}
