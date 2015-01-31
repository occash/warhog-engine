#ifndef GLCONTEXT_H
#define GLCONTEXT_H

#include "../../global.h"
#include "glformat.h"

class Window;

/*! \brief This class encapsulates OpenGL rendering context.

	A context stores all of the state associated with this instance of OpenGL. 
	The rendering context and frame buffer hints is set in constructor, however
	you can set it later with setContextHints() and setFramebufferHints().

	The makeCurrent() function makes this context the current rendering context.

	TODO: explicit create() function, doneCurrent(), reset(), contextHints(), framebufferHints()
	TODO: switch to GLFormat?
*/

class ENGINE_EXPORT GLContext
{
public:
    GLContext(const GLFormat& context = GLFormat());
    ~GLContext();

    bool makeCurrent(std::shared_ptr<Window> w);

private:
    GLFormat _context;

};

#endif
