#include "glrenderer.h"
#include "glwindow.h"
#include "glmesh.h"
#include "glshader.h"

const char * GLRenderer::name() const
{
	return "OpenGL";
}

Window *GLRenderer::createWindow()
{
	return new GLWindow();
}

Texture *GLRenderer::createTexture()
{
	return nullptr;
}

Mesh *GLRenderer::createMesh()
{
	return new GLMesh();
}

Shader *GLRenderer::createShader()
{
	return new GLShader();
}
