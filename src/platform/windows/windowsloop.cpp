#include "windowsloop.h"

#include <Windows.h>

WindowsLoop::WindowsLoop()
{

}

WindowsLoop::~WindowsLoop()
{

}

void WindowsLoop::update()
{
    MSG message;
    while (PeekMessage(&message, NULL, 0, 0, PM_NOREMOVE))
    {
        if (GetMessage(&message, NULL, 0, 0) == 0) break;
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
}
