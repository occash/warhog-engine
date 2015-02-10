#include "platformmanager.h"
#include "global.h"
#include "plugin.h"
#include "nativeinterface.h"


PlatformManager::PlatformManager()
	: _loader("platform"),
	_interface(nullptr)
{
	_loader.load();
	Plugin *plugin = _loader.plugin();
	if (!plugin)
		exit(0); // Cannot load platform? Panic

	_interface = dynamic_cast<NativeInterface *>(plugin);
}

PlatformManager *PlatformManager::instance()
{
	static PlatformManager manager;
	return &manager;
}

NativeLoop * PlatformManager::loop() const
{
	return _interface->loop();
}

NativeScreen * PlatformManager::screen() const
{
	return nullptr;// _interface->screen();
}

NativeWindow * PlatformManager::window() const
{
	return _interface->window();
}

NativeInput * PlatformManager::input() const
{
	return _interface->input();
}

NativeContext * PlatformManager::context() const
{
	return _interface->context("");
}
