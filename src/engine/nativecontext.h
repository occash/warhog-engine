#ifndef NATIVECONTEXT_H
#define NATIVECONTEXT_H

#include "surfaceformat.h"

class Window;

class NativeContext
{
public:
	SurfaceFormat format() const;
	void setFormat(const SurfaceFormat&);

	void makeCurrent(Window *);
	void doneCUrrent();

};

#endif //NATIVECONTEXT_H
