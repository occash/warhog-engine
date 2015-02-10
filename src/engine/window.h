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
	void showNormal();
	void hide();
	bool isFullscreen() const;
	void showFullscreen();
	bool isMinimized() const;
	void showMinimized();
	bool isMaximized() const;
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

	bool isActiveWindow() const;
	void activateWindow();
	
	bool isMouseGrabbed() const;
	void grabMouse();
	void releaseMouse();

	bool isCursorVisible() const;
	void showCursor();
	void hideCursor();

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
	friend class Context;
	NativeWindow *_window;

};

#endif