#ifndef WINDOW_H
#define WINDOW_H

#include "global.h"

struct WindowData;

class ENGINE_EXPORT Window
{
public:
	enum WindowFlags
	{
		Resizable = 1 << 0,
		Closable = 1 << 1,
		GrabMouse = 1 << 2,
		DestroyOnClose = 1 << 3
	};

    Window(int style, char *title = "Warhog", int width = 640, int height = 480);
    virtual ~Window();

	int x() const;
	int y() const;
	int width() const;
	int height() const;
	char *title() const;
	bool isVisible() const;
	bool isGrabMouse() const;

	void setPosition(int x, int y);
	void setSize(int w, int h);
	void setTitle(const char *title);
	void setVisible(bool v);
	void setMouseGrab(bool g);

	void show();
	void hide();
	void showFullscreen();
	void close();
	void update();

	static bool platformEvent(Window *, void *, long *);

protected:
	virtual void create(void *data);
	virtual void destroy(void *data);
	virtual void closeEvent();
	virtual void moveEvent(int x, int y);
	virtual void resizeEvent(int w, int h);
	virtual void focusInEvent();
	virtual void focusOutEvent();
	virtual void showEvent();
	virtual void hideEvent();

private:
	WindowData *_data;

};

#endif