#ifndef NATIVECONTEXT_H
#define NATIVECONTEXT_H

#include "surfaceformat.h"
#include "context.h"

class NativeWindow;

class NativeContext
{
public:
    virtual SurfaceFormat format() const = 0;
    virtual void setFormat(const SurfaceFormat&) = 0;

    virtual void create() = 0;
    virtual void destroy() = 0;

    virtual void makeCurrent(NativeWindow *) = 0;
    virtual void doneCurrent() = 0;

    virtual void swapBuffers() = 0;

    virtual GLFunction resolve(const char *) const = 0;

};

#endif //NATIVECONTEXT_H
