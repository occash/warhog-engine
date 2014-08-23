#ifndef RENDERER_H
#define RENDERER_H

#include "../global.h"

class Window;
class Mesh;
class Material;

class ENGINE_EXPORT Renderer
{
public:
	virtual Window *createWindow();
	virtual Mesh *createMesh();
	virtual Material *createMaterial();

};

#endif