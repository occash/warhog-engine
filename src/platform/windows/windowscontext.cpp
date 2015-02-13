#include "windowscontext.h"
#include "windowswindow.h"
#include "wgl.h"

#include <gl/GL.h>
#include "wglext.h"

//Resolve wgl functions first
static WGL wglcontext;

//Extensions
static PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = NULL;
static PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;
static PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = NULL;

//Resolve extensions
static bool resolveWglExt(PIXELFORMATDESCRIPTOR *pfd)
{
	WindowsWindow w;
	w.create();

	HWND handle = (HWND)w.handle();
	HDC hdc = GetDC(handle);

	// choose pixel format
	int pixelformat = ChoosePixelFormat(hdc, pfd);
	SetPixelFormat(hdc, pixelformat, pfd);

	// create simple context
	HGLRC context = wgl::CreateContext(hdc);
	wgl::MakeCurrent(hdc, context);
	//TODO: handle errors

	wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wgl::GetProcAddress("wglChoosePixelFormatARB");
	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wgl::GetProcAddress("wglCreateContextAttribsARB");
	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wgl::GetProcAddress("wglSwapIntervalEXT");

	// destroy context
	wgl::MakeCurrent(hdc, NULL);
	wgl::DeleteContext(context);

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
		*aptr++ = 1;
		*aptr++ = WGL_ACCELERATION_ARB;
		*aptr++ = WGL_FULL_ACCELERATION_ARB;
		*aptr++ = WGL_DOUBLE_BUFFER_ARB;
		*aptr++ = 1;
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

struct ContextData
{
	HWND hwnd = HWND();
	HDC hdc = HDC();
	HGLRC context = HGLRC();
};

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
		resolved = resolveWglExt(&pfd);

	//Create dummy window
	WindowsWindow w;
	w.create();
	HWND hwnd = (HWND)w.handle();
	HDC hdc = GetDC(hwnd);

	choosePixelFormat(&hdc, &pfd);

	HGLRC old_context = _data->context;
	_data->context = wgl::CreateContext(hdc);
	wgl::ShareLists(old_context, _data->context);

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
	wgl::DeleteContext(_data->context);
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
	wgl::MakeCurrent(_data->hdc, _data->context);
}

void WindowsContext::doneCurrent()
{
	wgl::MakeCurrent(_data->hdc, NULL);
	ReleaseDC(_data->hwnd, _data->hdc);
	_data->hwnd = HWND();
	_data->hdc = HDC();
}

void WindowsContext::swapBuffers()
{
	SwapBuffers(_data->hdc);
}

GLFunction WindowsContext::resolve(const char *symbol) const
{
	std::string name = symbol;
	GLFunction func = (GLFunction)wgl::GetProcAddress(name.c_str());
	if (!func) func = (GLFunction)wgl::GetProcAddress((name + "ARB").c_str());
	if (!func) func = (GLFunction)wgl::GetProcAddress((name + "EXT").c_str());
	if (!func) func = (GLFunction)wglcontext.resolve(name.c_str());
	return func;
}