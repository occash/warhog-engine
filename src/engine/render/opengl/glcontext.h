#ifndef GLCONTEXT_H
#define GLCONTEXT_H

#include "../../global.h"
#include "../../hints.h"

class Window;

/*! \brief This class encapsulates OpenGL rendering context.
*
* A context stores all of the state associated with this instance of OpenGL. 
* The rendering context and framebuffer hints is set in constructor, however
* you can set it later with setContextHints() and setFramebufferHints().
* 
* The makeCurrent() function makes this context the current rendering context.
*
* TODO: explicit create() function, doneCurrent(), reset(), contextHints(), framebufferHints()
* TODO: switch to GLFormat?
*/

class ENGINE_EXPORT GLContext
{
public:
    
    GLContext(const GLContextHints& context = GLContextHints(),
        const GLFramebufferHints& frame = GLFramebufferHints());
    ~GLContext();

    bool makeCurrent(std::shared_ptr<Window> w);

private:
    void setContext(const GLContextHints& context);
    void setFrameBuffer(const GLFramebufferHints& frame);

private:
    GLContextHints _context;
    GLFramebufferHints _frame;

};

#endif
