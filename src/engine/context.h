#ifndef CONTEXT_H
#define CONTEXT_H

#include "global.h"

class Window;
class NativeContext;

class ENGINE_EXPORT Context
{
public:
	Context();
	~Context();

	void makeCurrent(Window *window);
	void doneCurrent();

	void swapBuffers();

private:
	NativeContext *_context;

};

#endif //CONTEXT_H