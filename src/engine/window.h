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
	void showFullscreen();
	void hide();
	void close();

	int x() const;
	int y() const;
	int width() const;
	int height() const;
	void move(int x, int y);
	void resize(int w, int h);

	std::string title() const;
	void setTitle(const std::string& title);

	/*static bool platformEvent(Window *, void *, long *);

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
	virtual void updateEvent();*/

private:
	NativeWindow *_window;

};

#endif