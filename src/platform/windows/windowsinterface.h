#ifndef WINDOWSINTERFACE_H
#define WINDOWSINTERFACE_H

#include <nativeinterface.h>
#include <plugin.h>

class WindowsInterface : public NativeInterface, 
						 public Plugin
{
public:
	NativeLoop *loop() const override;

	NativeScreen * screen(int) override;
	NativeScreen * primaryScreen() override;
	int screenCount() override;

	NativeWindow *window() const override;
	NativeInput *input() const override;
	NativeContext *context(const char *) const override;

	const char *name() const override;
	const char *description() const override;
	const char *version() const override;
	const char *author() const override;

};

#endif //WINDOWSINTERFACE_H
