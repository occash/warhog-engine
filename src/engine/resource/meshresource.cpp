#include "meshresource.h"
#include "../render/renderer.h"

#include <iostream>

MeshResource::MeshResource(Renderer *renderer) :
	_renderer(renderer)
{
}

bool MeshResource::load(std::istream& in, Object *&resource) const
{
    Mesh *mesh = _renderer->createMesh();
    std::vector<Vertex>::size_type vertSize = 0;
    std::vector<unsigned int>::size_type indSize = 0;

    in.read((char *)&vertSize, sizeof(std::vector<Vertex>::size_type));
    in.read((char *)&indSize, sizeof(std::vector<unsigned int>::size_type));

	mesh->verticies.resize(vertSize);
    mesh->indices.resize(indSize);

	if (vertSize > 0)
        in.read((char *)mesh->verticies.data(),
        vertSize * sizeof(Vertex));
    if (indSize > 0)
        in.read((char *)mesh->indices.data(),
        mesh->indices.size() * sizeof(unsigned int));

    resource = mesh;

    return true;
}

bool MeshResource::save(std::ostream& out, Object *resource) const
{
    const Mesh *mesh = reinterpret_cast<const Mesh *>(resource);

	std::vector<Vertex>::size_type vertSize = mesh->verticies.size();
    std::vector<unsigned int>::size_type indSize = mesh->indices.size();

	out.write((char *)&vertSize,
        sizeof(std::vector<Vertex>::size_type));
    out.write((char *)&indSize,
        sizeof(std::vector<unsigned int>::size_type));

	out.write((char *)mesh->verticies.data(),
		vertSize * sizeof(Vertex));
    out.write((char *)mesh->indices.data(),
        indSize * sizeof(unsigned int));

    return true;
}
