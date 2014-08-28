#ifndef GLRENDERER_H
#define GLRENDERER_H

#include "../renderer.h"

class GLRenderer : public Renderer
{
public:
	const char *name() const override;
	Window *createWindow() override;
	Texture *createTexture() override;
	Mesh *createMesh() override;
	Shader *createShader() override;

};

#endif