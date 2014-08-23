#include "glrenderer.h"
#include "glwindow.h"
#include "glmesh.h"
#include "glmaterial.h"

Window * GLRenderer::createWindow()
{
	return new GLWindow();
}

Mesh *GLRenderer::createMesh()
{
	return new GLMesh();
}

Material * GLRenderer::createMaterial()
{
	return new GLMaterial();
}
