#ifndef GLWINDOW_H
#define GLWINDOW_H

#include "../../window.h"

struct GLWindowData;

class GLWindow : public Window
{
public:
	GLWindow();
	~GLWindow();

/*protected:
	void resizeEvent(int w, int h);
	void updateEvent() override;
	void create(void *data) override;
	void destroy(void *data) override;*/

private:
	GLWindowData *_data;

};

#endif