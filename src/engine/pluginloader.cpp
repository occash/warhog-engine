#include "pluginloader.h"
#include "meta/object.h"

typedef Object*(*PluginEntry)();

PluginLoader::PluginLoader()
	: _library()
{
}

PluginLoader::PluginLoader(const std::string& name)
	: _library(name)
{
}

PluginLoader::~PluginLoader()
{
}

std::string PluginLoader::name() const
{
	return _library.name();
}

void PluginLoader::setName(const std::string& name)
{
	_library.setName(name);
}

bool PluginLoader::load()
{
	return _library.load();
}

bool PluginLoader::unload()
{
	return _library.unload();
}

Object * PluginLoader::object() const
{
	PluginEntry entry = (PluginEntry)_library.resolve("pluginEntry");
	if (!entry)
		return nullptr;

	return entry();
}
