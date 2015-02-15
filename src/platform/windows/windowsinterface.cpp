#include "windowsinterface.h"
#include "windowsloop.h"
#include "windowswindow.h"
#include "windowscontext.h"


NativeLoop *WindowsInterface::loop() const
{
    return new WindowsLoop();
}

NativeScreen *WindowsInterface::screen(int)
{
    return nullptr;
}

NativeWindow *WindowsInterface::window() const
{
    return new WindowsWindow();
}

NativeInput *WindowsInterface::input() const
{
    return nullptr;
}

NativeContext *WindowsInterface::context(const char *) const
{
    return new WindowsContext();;
}

const char *WindowsInterface::name() const
{
    return "WindowsPlatform";
}

const char *WindowsInterface::description() const
{
    return "Windows platform interface";
}

const char *WindowsInterface::version() const
{
    return "1.0";
}

const char *WindowsInterface::author() const
{
    return "Warhog Team";
}

NativeScreen *WindowsInterface::primaryScreen()
{
    return nullptr;
}

int WindowsInterface::screenCount()
{
    return 0;
}
