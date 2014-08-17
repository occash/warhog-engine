#ifndef WINDOW_H
#define WINDOW_H

#include "global.h"

struct WindowData;

class ENGINE_EXPORT Window
{
public:
	enum WindowStyle
	{
		Resizable,
		Closable
	};

	enum Event
	{
		Move,
		Resize,
		Close,
		Visible
	};

    Window(int style);
    virtual ~Window();

	int x() const;
	int y() const;
	int width() const;
	int height() const;

	void setPosition(int x, int y);
	void setSize(int w, int h);

	void setTitle(const char *title);
	void setVisible(bool v);
	void show();
	void hide();
	void showFullscreen();
	void close();
	void update();
	void event(Event);

protected:
	virtual void create(void *data);
	virtual void destroy(void *data);
	virtual void moveEvent();
	virtual void resizeEvent();
	virtual void closeEvent();
	virtual void visibleEvent();

private:
	WindowData *_data;

};

#endif