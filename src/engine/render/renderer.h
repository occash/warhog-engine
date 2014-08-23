#ifndef RENDERER_H
#define RENDERER_H

class Window;
class Mesh;

class Renderer
{
public:
	virtual Window *createWindow();
	virtual Mesh *createMesh();
	//virtual Texture *createTexture();
	//virtual Shader *createShader();

};

#endif