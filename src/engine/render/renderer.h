#ifndef RENDERER_H
#define RENDERER_H

#include "../global.h"

class Window;
class Texture;
class Mesh;
class Shader;

class ENGINE_EXPORT Renderer
{
public:
	virtual const char *name() const;

	virtual Window *createWindow();
	virtual Texture *createTexture();
	virtual Mesh *createMesh();
	virtual Shader *createShader();

};

#endif