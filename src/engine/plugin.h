#ifndef PLUGIN_H
#define PLUGIN_H

#include "global.h"

class Plugin
{
public:
	virtual const char *name() const = 0;
	virtual const char *description() const = 0;
	virtual const char *version() const = 0;
	virtual const char *author() const = 0;
};

#define EXPORT_PLUGIN(Class) \
	extern "C" { \
		DECL_EXPORT Plugin *pluginEntry() \
		{ \
			static Class plugin; \
			return dynamic_cast<Plugin*>(&plugin); \
		} \
	}

#endif
