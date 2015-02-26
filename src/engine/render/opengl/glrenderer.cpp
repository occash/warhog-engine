#include "glrenderer.h"
#include "gltexture.h"
#include "glmesh.h"
#include "glshader.h"
#include "glquery.h"
#include "glextensions.h"

GLRenderer::GLRenderer()
{
}

GLRenderer::~GLRenderer()
{
}

const char *GLRenderer::name() const
{
    return "OpenGL";
}

Window *GLRenderer::createWindow()
{
    return nullptr;
}

Texture *GLRenderer::createTexture()
{
    return new GLTexture();
}

Mesh *GLRenderer::createMesh()
{
    return new GLMesh();
}

Shader *GLRenderer::createShader()
{
    return new GLShader();
}

void GLRenderer::createOcclusionQuery()
{
    occlusionQuery = new GLQuery(GL_ANY_SAMPLES_PASSED);
}

void GLRenderer::beginOcclusionQuery()
{
    occlusionQuery->begin();
}

bool GLRenderer::endOcclusionQuery()
{
    occlusionQuery->end();
    while (!occlusionQuery->ready());
    return occlusionQuery->result() > 0;
}
