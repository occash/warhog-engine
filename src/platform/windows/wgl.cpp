#include "wgl.h"

namespace wgl
{
    PFNWGLCREATECONTEXT CreateContext = NULL;
    PFNWGLDELETECONTEXT DeleteContext = NULL;
    PFNWGLGETCURRENTCONTEXT GetCurrentContext = NULL;
    PFNWGLGETCURRENTDC GetCurrentDC = NULL;
    PFNWGLGETPROCADDRESS GetProcAddress = NULL;
    PFNWGLMAKECURRENT MakeCurrent = NULL;
    PFNWGLSHARELISTS ShareLists = NULL;
};

WGL::WGL()
{
    _handle = LoadLibrary("opengl32.dll");
    if (_handle == NULL)
    {
        MessageBox(NULL, TEXT("Cannot find OpenGL in system"), TEXT("Fatal error"), MB_OK);
        exit(1);
    }

    wgl::CreateContext = (PFNWGLCREATECONTEXT)GetProcAddress(_handle, "wglCreateContext");
    wgl::DeleteContext = (PFNWGLDELETECONTEXT)GetProcAddress(_handle, "wglDeleteContext");
    wgl::GetCurrentContext = (PFNWGLGETCURRENTCONTEXT)GetProcAddress(_handle, "wglGetCurrentContext");
    wgl::GetCurrentDC = (PFNWGLGETCURRENTDC)GetProcAddress(_handle, "wglGetCurrentDC");
    wgl::GetProcAddress = (PFNWGLGETPROCADDRESS)GetProcAddress(_handle, "wglGetProcAddress");
    wgl::MakeCurrent = (PFNWGLMAKECURRENT)GetProcAddress(_handle, "wglMakeCurrent");
    wgl::ShareLists = (PFNWGLSHARELISTS)GetProcAddress(_handle, "wglShareLists");
}

WGL::~WGL()
{
    FreeLibrary(_handle);
}

void *WGL::resolve(const char *symbol)
{
    return (void *)GetProcAddress(_handle, symbol);
}