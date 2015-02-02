#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "global.h"

class NativeLoop;

class ENGINE_EXPORT Dispatcher
{
public:
	Dispatcher();
	~Dispatcher();

	void update();

private:
	NativeLoop *_loop;
};

#endif //DISPATCHER_H
