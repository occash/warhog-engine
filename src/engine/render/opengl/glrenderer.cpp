#include "glrenderer.h"
#include "glwindow.h"

Window * GLRenderer::createWindow()
{
	return new GLWindow();
}
