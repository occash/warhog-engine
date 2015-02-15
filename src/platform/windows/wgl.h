#ifndef WGL_H
#define WGL_H

#include <Windows.h>

class WGL
{
public:
    WGL();
    ~WGL();

    void *resolve(const char *);

private:
    HMODULE _handle;

};

typedef HGLRC(WINAPI *PFNWGLCREATECONTEXT)(HDC);
typedef BOOL(WINAPI *PFNWGLDELETECONTEXT)(HGLRC);
typedef HGLRC(WINAPI *PFNWGLGETCURRENTCONTEXT)(VOID);
typedef HDC(WINAPI *PFNWGLGETCURRENTDC)(VOID);
typedef PROC(WINAPI *PFNWGLGETPROCADDRESS)(LPCSTR);
typedef BOOL(WINAPI *PFNWGLMAKECURRENT)(HDC, HGLRC);
typedef BOOL(WINAPI *PFNWGLSHARELISTS)(HGLRC, HGLRC);

namespace wgl
{
    extern PFNWGLCREATECONTEXT CreateContext;
    extern PFNWGLDELETECONTEXT DeleteContext;
    extern PFNWGLGETCURRENTCONTEXT GetCurrentContext;
    extern PFNWGLGETCURRENTDC GetCurrentDC;
    extern PFNWGLGETPROCADDRESS GetProcAddress;
    extern PFNWGLMAKECURRENT MakeCurrent;
    extern PFNWGLSHARELISTS ShareLists;
};

#endif //WGL_H