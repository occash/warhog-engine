#ifndef GLWINDOW_H
#define GLWINDOW_H

#include "../../window.h"

class GLWindowData;

class GLWindow : public Window
{
protected:
	void create(WindowData *data);
};

#endif