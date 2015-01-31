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

GLContext::GLContext(const GLContextHints& context, 
    const GLFramebufferHints& frame)
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

void GLContext::setContext(const GLContextHints& context)
{
    //Set context hints
    /*glfwWindowHint(GLFW_CLIENT_API, context.api);
    glfwWindowHint(GLFW_OPENGL_PROFILE, context.profile);
    glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, context.strategy);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, context.major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, context.minor);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, context.debug ? GL_TRUE : GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, context.forward ? GL_TRUE : GL_FALSE);*/
}

void GLContext::setFrameBuffer(const GLFramebufferHints& frame)
{
    //Set context hints
    /*glfwWindowHint(GLFW_RED_BITS, frame.redBits);
    glfwWindowHint(GLFW_GREEN_BITS, frame.greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, frame.blueBits);
    glfwWindowHint(GLFW_ALPHA_BITS, frame.alphaBits);

    glfwWindowHint(GLFW_DEPTH_BITS, frame.depthBits);
    glfwWindowHint(GLFW_STENCIL_BITS, frame.stensilBits);

    glfwWindowHint(GLFW_ACCUM_RED_BITS, frame.redAccum);
    glfwWindowHint(GLFW_ACCUM_GREEN_BITS, frame.greenAccum);
    glfwWindowHint(GLFW_ACCUM_BLUE_BITS, frame.blueAccum);
    glfwWindowHint(GLFW_ACCUM_ALPHA_BITS, frame.alphaAccum);

    glfwWindowHint(GLFW_AUX_BUFFERS, frame.auxBuffers);
    glfwWindowHint(GLFW_SAMPLES, frame.samples);
    glfwWindowHint(GLFW_REFRESH_RATE, frame.refreshRate);

    glfwWindowHint(GLFW_STEREO, frame.stereo ? GL_TRUE : GL_FALSE);
    glfwWindowHint(GLFW_SRGB_CAPABLE, frame.srgb ? GL_TRUE : GL_FALSE);*/
}
