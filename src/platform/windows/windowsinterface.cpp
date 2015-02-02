#include "windowsinterface.h"
#include "windowsloop.h"
#include "windowswindow.h"


NativeLoop *WindowsInterface::loop() const
{
	return new WindowsLoop();
}

NativeScreen *WindowsInterface::screen() const
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

NativeGLContext *WindowsInterface::glContext() const
{
	return nullptr;
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
