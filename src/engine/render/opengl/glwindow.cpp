#include "glwindow.h"
#include "glextensions.h"

#include <windows.h>
//#include "GL/GL.h"
//#include "wglext.h"

struct GLWindowData
{
	HDC hdc;
	HGLRC context;
};

/*static PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = NULL;
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
	GLExt::init();

	wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
	//TODO: handle errors

	// destroy context
	wglMakeCurrent(*hdc, NULL);
	wglDeleteContext(*context);
	*context = NULL;
}*/

GLWindow::GLWindow() :
	Window(/*Window::Closable | Window::Resizable | Window::DestroyOnClose*/),
	_data(new GLWindowData)
{
	_data->hdc = HDC();
	_data->context = HGLRC();
}

GLWindow::~GLWindow()
{
}

/*void GLWindow::create(void *data)
{
	HWND window = (HWND)data;

	// pixel format descriptor
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_SWAP_EXCHANGE,
		PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 8, 0, PFD_MAIN_PLANE, 0, 0, 0, 0
	};

	_data->hdc = GetDC(window);
	if (!wglChoosePixelFormatARB)
		resolveWgl(&_data->hdc, &_data->context, &pfd);

	//Create OpenGL context
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
		wglChoosePixelFormatARB(_data->hdc, attributes, NULL, 1, &pixelformat, &count);
		if (count == 0) pixelformat = ChoosePixelFormat(_data->hdc, &pfd);

		// set pixel format
		SetPixelFormat(_data->hdc, pixelformat, &pfd);

		HGLRC old_context = _data->context;
		_data->context = wglCreateContext(_data->hdc);
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
			_data->context = wglCreateContextAttribsARB(_data->hdc, _data->context, attributes);
		}

		wglMakeCurrent(_data->hdc, _data->context);
	}

	//TODO: setup vertical sync
	//wglSwapIntervalEXT

	// clear buffers
	glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glClearStencil(0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void GLWindow::destroy(void *data)
{

}

void GLWindow::updateEvent()
{
	SwapBuffers(_data->hdc);
}

void GLWindow::resizeEvent(int w, int h)
{
	glViewport(0, 0, w, h);
}
*/
