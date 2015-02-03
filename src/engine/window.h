#ifndef WINDOW_H
#define WINDOW_H

#include "global.h"
#include <string>

class NativeWindow;

class ENGINE_EXPORT Window
{
public:
    Window();
    ~Window();

	bool isVisible() const;
	void show();
	void hide();
	void showNormal();
	void showFullscreen();
	void showMinimized();
	void showMaximized();
	void close();

	int x() const;
	int y() const;
	int width() const;
	int height() const;
	void move(int x, int y);
	void resize(int w, int h);

	std::string title() const;
	void setTitle(const std::string& title);
	
	bool isMouseGrabbed() const;
	void grabMouse();
	void releaseMouse();

	/*static bool platformEvent(Window *, void *, long *);

protected:
	virtual void create();
	virtual void destroy();
	virtual void closeEvent();
	virtual void moveEvent(int x, int y);
	virtual void resizeEvent(int w, int h);
	virtual void focusInEvent();
	virtual void focusOutEvent();
	virtual void showEvent();
	virtual void hideEvent();
	virtual void updateEvent();*/

private:
	NativeWindow *_window;

};

#endif