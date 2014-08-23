#include "glrenderer.h"
#include "glwindow.h"
#include "glmesh.h"

Window * GLRenderer::createWindow()
{
	return new GLWindow();
}

Mesh *GLRenderer::createMesh()
{
	return new GLMesh();
}
