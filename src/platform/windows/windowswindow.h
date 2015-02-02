#ifndef WINDOWSWINDOW_H
#define WINDOWSWINDOW_H

#include <nativewindow.h>

class WindowsWindow : public NativeWindow
{
public:
	WindowsWindow();
	~WindowsWindow();

	void create() override;
	void destroy() override;

	bool isVisible() const override;
	void setVisible(bool visible) override;
	bool isFullscreen() const override;
	void setFullscreen(bool fullscreen) override;
	void close() override;

	int x() const override;
	int y() const override;
	int width() const override;
	int height() const override;
	void move(int x, int y) override;
	void resize(int w, int h) override;

	const char *title() const override;
	void setTitle(const char *title) override;

	bool mouseGrab() const override;
	void setMouseGrab(bool) override;

	static bool platformEvent(WindowsWindow *window, void *msgPtr, long *result);

private:
	friend struct WindowData;
	WindowData *_data;
};

#endif //WINDOWSWINDOW_H
