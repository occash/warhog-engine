#ifndef PLUGIN_H
#define PLUGIN_H

#define EXPORT_PLUGIN(Plugin) \
	Object *pluginEntry()
	{ \
		static Plugin plugin; \
		return dynamic_cast<Object *>(&plugin); \
	}

#endif
