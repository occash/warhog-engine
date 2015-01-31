#include "glcontext.h"
#include "../../window.h"

//GL related
#include "glextensions.h"

//Standard library
#include <iostream>

//Platform specific
#include <Windows.h>

void error_callback(int error, const char* description)
{
    MessageBoxA(NULL, description, "Error", MB_OK);
    exit(1);
}

GLContext::GLContext(const GLFormat& context)
{
    /*//Set error handling before init
    glfwSetErrorCallback(error_callback);

    //Initialize GLFW lib
    GLint res = glfwInit();

    _context = context;
    setContext(context);

    _frame = frame;
    setFrameBuffer(frame);*/
}

GLContext::~GLContext()
{
    //glfwTerminate();
}

bool GLContext::makeCurrent(std::shared_ptr<Window> w)
{
    /*glfwMakeContextCurrent(w->_handle);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    return (err == GLEW_OK);*/
	return false;
}