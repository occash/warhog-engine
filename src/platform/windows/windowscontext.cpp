#include "windowscontext.h"
#include "windowswindow.h"

#include <Windows.h>
#include <GL/GL.h>
#include "wglext.h"

struct ContextData
{
	HWND hwnd = HWND();
	HDC hdc = HDC();
	HGLRC context = HGLRC();
};

static PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = NULL;
static PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;
static PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = NULL;

static bool resolveWgl(PIXELFORMATDESCRIPTOR *pfd)
{
	WindowsWindow w;
	w.create();

	HWND handle = (HWND)w.handle();
	HDC hdc = GetDC(handle);

	// choose pixel format
	int pixelformat = ChoosePixelFormat(hdc, pfd);
	SetPixelFormat(hdc, pixelformat, pfd);

	// create simple context
	HGLRC context = wglCreateContext(hdc);
	//wglShareLists(old_context, *context);
	wglMakeCurrent(hdc, context);
	//TODO: handle errors

	//resolve opengl functions
	//GLExt::init();

	wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
	//TODO: handle errors

	// destroy context
	wglMakeCurrent(hdc, NULL);
	wglDeleteContext(context);

	ReleaseDC(handle, hdc);

	w.destroy();

	return true;
}

static bool resolved = false;

void choosePixelFormat(HDC *hdc, PIXELFORMATDESCRIPTOR *pfd)
{
	if (wglChoosePixelFormatARB) {
		//Create attributes
		int attributes[128];
		memset(attributes, 0, sizeof(attributes));
		int *aptr = attributes;

		*aptr++ = WGL_DRAW_TO_WINDOW_ARB;
		*aptr++ = GL_TRUE;
		*aptr++ = WGL_ACCELERATION_ARB;
		*aptr++ = WGL_FULL_ACCELERATION_ARB;
		*aptr++ = WGL_DOUBLE_BUFFER_ARB;
		*aptr++ = GL_TRUE;
		*aptr++ = WGL_COLOR_BITS_ARB;
		*aptr++ = 32;
		*aptr++ = WGL_DEPTH_BITS_ARB;
		*aptr++ = 24;
		*aptr++ = WGL_STENCIL_BITS_ARB;
		*aptr++ = 8;
		//TODO: add multisampling

		// choose pixel format
		int pixelformat;
		unsigned int count;
		wglChoosePixelFormatARB(*hdc, attributes, NULL, 1, &pixelformat, &count);
		if (count == 0) pixelformat = ChoosePixelFormat(*hdc, pfd);

		// set pixel format
		SetPixelFormat(*hdc, pixelformat, pfd);
	}
}

WindowsContext::WindowsContext()
	: _data(new ContextData)
{
}

WindowsContext::~WindowsContext()
{
	delete _data;
}

SurfaceFormat WindowsContext::format() const
{
	return _format;
}

void WindowsContext::setFormat(const SurfaceFormat& format)
{
	_format = format;
}

void WindowsContext::create()
{
	//TODO set format
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_SWAP_EXCHANGE,
		PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 8, 0, PFD_MAIN_PLANE, 0, 0, 0, 0
	};

	if (!resolved)
		resolved = resolveWgl(&pfd);

	//Create dummy window
	WindowsWindow w;
	w.create();
	HWND hwnd = (HWND)w.handle();
	HDC hdc = GetDC(hwnd);

	choosePixelFormat(&hdc, &pfd);

	HGLRC old_context = _data->context;
	_data->context = wglCreateContext(hdc);
	wglShareLists(old_context, _data->context);

	// create context attributes
	if (wglCreateContextAttribsARB)
	{
		//Create attributes
		int attributes[128];
		memset(attributes, 0, sizeof(attributes));

#ifndef DEBUG
		int *aptr = attributes;
		*aptr++ = WGL_CONTEXT_FLAGS_ARB;
		*aptr++ = WGL_CONTEXT_DEBUG_BIT_ARB;
#endif

		// create context attributes
		_data->context = wglCreateContextAttribsARB(hdc, _data->context, attributes);
	}

	ReleaseDC(hwnd, hdc);
	w.destroy();
}

void WindowsContext::destroy()
{
	wglDeleteContext(_data->context);
	_data->context = HGLRC();
}

void WindowsContext::makeCurrent(NativeWindow *window)
{
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_SWAP_EXCHANGE,
		PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 8, 0, PFD_MAIN_PLANE, 0, 0, 0, 0
	};

	WindowsWindow *w = static_cast<WindowsWindow *>(window);
	_data->hwnd = (HWND)w->handle();
	_data->hdc = GetDC(_data->hwnd);

	choosePixelFormat(&_data->hdc, &pfd);
	wglMakeCurrent(_data->hdc, _data->context);
}

void WindowsContext::doneCurrent()
{
	wglMakeCurrent(_data->hdc, NULL);
	ReleaseDC(_data->hwnd, _data->hdc);
	_data->hwnd = HWND();
	_data->hdc = HDC();
}

void WindowsContext::swapBuffers()
{
	SwapBuffers(_data->hdc);
}
