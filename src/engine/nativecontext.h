#ifndef NATIVECONTEXT_H
#define NATIVECONTEXT_H

#include "surfaceformat.h"

class Window;

class NativeContext
{
public:
	virtual SurfaceFormat format() const = 0;
	virtual void setFormat(const SurfaceFormat&) = 0;

	virtual void makeCurrent(Window *) = 0;
	virtual void doneCUrrent() = 0;

};

#endif //NATIVECONTEXT_H
