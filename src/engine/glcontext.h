#ifndef GLCONTEXT_H
#define GLCONTEXT_H

#include "global.h"
#include "hints.h"

class Window;

class ENGINE_EXPORT GLContext
{
public:
    
    GLContext(const GLContextHints& context = GLContextHints(),
        const GLFramebufferHints& frame = GLFramebufferHints());
    ~GLContext();

    bool makeCurrent(Ptr<Window> w);

private:
    void setContext(const GLContextHints& context);
    void setFrameBuffer(const GLFramebufferHints& frame);

private:
    GLContextHints _context;
    GLFramebufferHints _frame;

};

#endif
