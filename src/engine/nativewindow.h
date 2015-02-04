#ifndef NATIVEWINDOW_H
#define NATIVEWINDOW_H

#include "global.h"
#include "window.h"
#include "flags.h"

class NativeWindow
{
public:
	enum Style
	{
		Clozable,
		Resizable
	};

	enum State
	{
		Normal,
		Mimimized,
		Maximized,
		Fullsceren,
		Active
	};

	W_DECLAGE_FLAGS(Styles, Style)
	W_DECLAGE_FLAGS(States, State)

public:
	virtual void create() = 0;
	virtual void destroy() = 0;

	virtual bool isVisible() const = 0;
	virtual void setVisible(bool) = 0;

	virtual States states() = 0;
	virtual void setStates(States) = 0;

	virtual int x() const = 0;
	virtual int y() const = 0;
	virtual void move(int, int) = 0;

	virtual int width() const = 0;
	virtual int height() const = 0;
	virtual void resize(int, int) = 0;

	virtual const char *title() const = 0;
	virtual void setTitle(const char *) = 0;

	virtual bool isMouseGrabbed() const = 0;
	virtual void setMouseGrab(bool) = 0;

	virtual bool isCursorVisible() const = 0;
	virtual void setCursorVisible(bool visible) = 0;

};

#endif //NATIVEWINDOW_H
