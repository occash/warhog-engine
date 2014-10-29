#ifndef MESHFILTER_H
#define MESHFILTER_H

#include "../global.h"
#include <entityx/Entity.h>

class Mesh;

class ENGINE_EXPORT MeshFilterComponent : 
	public entityx::Component<MeshFilterComponent>
{
public:
	MeshFilterComponent();
	~MeshFilterComponent();

	Mesh *mesh() const;
	void setMesh(Mesh *mesh);

private:
	Mesh *_mesh;

};

#endif