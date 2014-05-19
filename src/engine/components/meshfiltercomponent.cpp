#include "meshfiltercomponent.h"
#include "../mesh.h"


MeshFilterComponent::MeshFilterComponent()
	: _mesh(nullptr)
{
}


MeshFilterComponent::~MeshFilterComponent()
{
}

Mesh *MeshFilterComponent::mesh() const
{
	return _mesh;
}

void MeshFilterComponent::setMesh(Mesh *mesh)
{
	_mesh = mesh;
}