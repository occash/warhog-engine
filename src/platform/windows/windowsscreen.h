#ifndef WINDOWSSCREEN_H
#define WINDOWSSCREEN_H

#include <NativeScreen.h>

class WindowsScreen : public NativeScreen
{
public:
	int width() override;
	int height() override;
	int refreshRate() override;
	int physicalWidth() override;
	int physicalHeight() override;

	void setVideoMode(int width, int height, int rate) override;

};

#endif //WINDOWSSCREEN_H