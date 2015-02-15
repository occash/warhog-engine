#ifndef GLX_H
#define GLX_H

#include "glxext.h"
#include<X11/Xlib.h>

class GLX
{
public:
    GLX();
    ~GLX();

    void *resolve(const char *);

private:
    void *_handle;

};

typedef XVisualInfo *(*PFNGLXCHOOSEVISUALPROC)(Display *, int, int *);
typedef GLXContext (*PFNGLXCREATECONTEXTPROC)(Display *, XVisualInfo *, GLXContext, Bool);
typedef void (*PFNGLXDESTROYCONTEXTPROC)(Display *, GLXContext);
typedef GLXContext (*PFNGLXGETCURRENTCONTEXTPROC)(void);
typedef GLXDrawable (*PFNGLXGETCURRENTDRAWABLEPROC)(void);
typedef Bool (*PFNGLXMAKECURRENTPROC)(Display *, GLXDrawable, GLXContext);
typedef void (*PFNGLXSWAPBUFFERSPROC)(Display *, GLXDrawable);
typedef const char *(*PFNGLXGETCLIENTSTRINGPROC)(Display *, int);
typedef Display *(*PFNGLXGETCURRENTDISPLAYPROC)(void);
typedef GLXFBConfig *(*PFNGLXCHOOSEFBCONFIGPROC)(Display *, int, const int *, int *);
typedef GLXPbuffer (*PFNGLXCREATEPBUFFERPROC)(Display *, GLXFBConfig, const int *);
typedef void (*PFNGLXDESTROYPBUFFERPROC)(Display *, GLXPbuffer);
typedef XVisualInfo *(*PFNGLXGETVISUALFROMFBCONFIGPROC)(Display *, GLXFBConfig);
typedef __GLXextFuncPtr (*PFNGLXGETPROCADDRESSPROC)(const GLubyte *);

namespace glx
{
    extern PFNGLXCHOOSEVISUALPROC ChooseVisual;
    //To be continue
};

#endif //GLX_H