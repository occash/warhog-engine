#include "windowscontext.h"
#include <Windows.h>
#include <GL/GL.h>
#include "wglext.h"

static PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = NULL;
static PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;
static PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = NULL;

void resolveWgl(HDC *hdc, HGLRC *context, PPIXELFORMATDESCRIPTOR pfd)
{
	// choose pixel format
	int pixelformat = ChoosePixelFormat(*hdc, pfd);
	SetPixelFormat(*hdc, pixelformat, pfd);

	// create simple context
	HGLRC old_context = *context;
	*context = wglCreateContext(*hdc);
	wglShareLists(old_context, *context);
	wglMakeCurrent(*hdc, *context);
	//TODO: handle errors

	//resolve opengl functions
	//GLExt::init();

	wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
	//TODO: handle errors

	// destroy context
	wglMakeCurrent(*hdc, NULL);
	wglDeleteContext(*context);
	*context = NULL;
}

WindowsContext::WindowsContext()
{
}

WindowsContext::~WindowsContext()
{
}

SurfaceFormat WindowsContext::format() const
{
	return SurfaceFormat();
}

void WindowsContext::setFormat(const SurfaceFormat &)
{
}

void WindowsContext::makeCurrent(Window *)
{
}

void WindowsContext::doneCUrrent()
{
}
