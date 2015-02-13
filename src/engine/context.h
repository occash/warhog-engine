#ifndef CONTEXT_H
#define CONTEXT_H

#include "global.h"

class Window;
class NativeContext;

typedef void(*GLFunction)();

class ENGINE_EXPORT Context
{
public:
	Context();
	~Context();

	void makeCurrent(Window *window);
	void doneCurrent();

	void swapBuffers();

	GLFunction resolve(const char *symbol) const;

private:
	NativeContext *_context;

};

#endif //CONTEXT_H