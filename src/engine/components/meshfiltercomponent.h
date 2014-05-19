#ifndef MESHFILTER_H
#define MESHFILTER_H

#include "../global.h"

#include <entityx/Entity.h>

using namespace entityx;
class Mesh;

class ENGINE_EXPORT MeshFilterComponent : public Component<MeshFilterComponent>
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