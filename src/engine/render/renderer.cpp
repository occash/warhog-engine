#include "renderer.h"

const char *Renderer::name() const
{
    return nullptr;
}

Window *Renderer::createWindow()
{
    return nullptr;
}

Texture *Renderer::createTexture()
{
    return nullptr;
}

Mesh *Renderer::createMesh()
{
    return nullptr;
}

Shader *Renderer::createShader()
{
    return nullptr;
}

void Renderer::createOcclusionQuery()
{

}

void Renderer::beginOcclusionQuery()
{

}

bool Renderer::endOcclusionQuery()
{
    return false;
}
