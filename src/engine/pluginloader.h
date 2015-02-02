#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include "global.h"
#include "library.h"

#include <string>

class Object;

class ENGINE_EXPORT PluginLoader
{
public:
	PluginLoader();
	PluginLoader(const std::string& name);
	~PluginLoader();

	std::string name() const;
	void setName(const std::string& name);

	bool load();
	bool unload();

	Object *object() const;

private:
	Library _library;

};

#endif //PLUGINLOADER_H
