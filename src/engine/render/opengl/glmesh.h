#ifndef GLMESH_H
#define GLMESH_H

#include "../../mesh.h"

class GLMesh : public Mesh
{
public:
	GLMesh();
	~GLMesh();

	void bind() override;
	void unbind() override;

	void load() override;
	void unload() override;

private:
	unsigned int _vao;
	unsigned int _vbo;
	unsigned int _ebo;

};

#endif