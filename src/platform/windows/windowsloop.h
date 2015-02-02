#ifndef WINDOWSLOOP_H
#define WINDOWSLOOP_H

#include <nativeloop.h>

class WindowsLoop : public NativeLoop
{
public:
	WindowsLoop();
	~WindowsLoop();

	void update() override;
};

#endif //WINDOWSLOOP_H
