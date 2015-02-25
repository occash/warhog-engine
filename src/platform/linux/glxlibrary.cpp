#include <dlfcn.h>
#include "glxlibrary.h"

namespace glx
{
    PFNGLXCHOOSEVISUALPROC ChooseVisual = NULL;
    //To be continue
};

GLX::GLX()
{
    _handle = dlopen("libGL.so.1", RTLD_GLOBAL | RTLD_LAZY);
    if (_handle == NULL)
        _handle = dlopen("libGL.so.1", RTLD_LAZY);

    if (!_handle)
        return; //Handle error (message box)

    glx::ChooseVisual = (PFNGLXCHOOSEVISUALPROC)dlsym(_handle, "glxChooseVisual");
    //To be continue
}

GLX::~GLX()
{
    dlclose(_handle);
}

void *GLX::resolve(const char *symbol)
{
    //Use glx::GetProcAddress
}