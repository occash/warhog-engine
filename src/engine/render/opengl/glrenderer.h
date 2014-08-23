#ifndef GLRENDERER_H
#define GLRENDERER_H

#include "../renderer.h"

class GLRenderer : public Renderer
{
public:
	Window *createWindow() override;
	Mesh *createMesh() override;

};

#endif