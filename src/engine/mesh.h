#ifndef MESH_H
#define MESH_H

#include "global.h"
#include "meta/object.h"

#include <vector>
#include <glm/glm.hpp>

struct Vertex
{
	float position[3];
	unsigned char boneweights[4];
	unsigned char boneindices[4];
	unsigned char normal[4];
	unsigned short int uv[2];
	unsigned char tangent[4];
};

class ENGINE_EXPORT Mesh : public Object
{
	OBJECT(Mesh, Object)
public:
	Mesh();
	~Mesh();

	virtual void bind();
	virtual void unbind();

	virtual void load();
	virtual void unload();

	virtual void draw();

    std::vector<Vertex> verticies;
    std::vector<unsigned int> indices;

};

#endif