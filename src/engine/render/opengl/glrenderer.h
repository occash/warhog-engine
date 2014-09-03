#ifndef GLRENDERER_H
#define GLRENDERER_H

#include "../renderer.h"
#include "glquery.h"

class GLRenderer : public Renderer
{
public:
	GLRenderer();
	~GLRenderer();

	const char *name() const override;

	Window *createWindow() override;
	Texture *createTexture() override;
	Mesh *createMesh() override;
	Shader *createShader() override;

	void createOcclusionQuery() override;
	void beginOcclusionQuery() override;
	bool endOcclusionQuery() override;

private:
	GLQuery *occlusionQuery;

};

#endif