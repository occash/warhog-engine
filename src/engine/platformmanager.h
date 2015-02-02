#ifndef PLATFORMMANAGER_H
#define PLATFORMMANAGER_H

#include "pluginloader.h"

class NativeInterface;
class NativeLoop;
class NativeScreen;
class NativeWindow;
class NativeInput;
class NativeGLContext;

class PlatformManager
{
public:
	static PlatformManager *instance();

	NativeLoop *loop() const;
	NativeScreen *screen() const;
	NativeWindow *window() const;
	NativeInput *input() const;
	NativeGLContext *glContext() const;

private:
	PlatformManager();

private:
	PluginLoader _loader;
	NativeInterface *_interface;

};

#endif //PLATFORMMANAGER_H
