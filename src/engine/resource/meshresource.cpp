#include "meshresource.h"

#include <iostream>

bool MeshResource::loadData(std::istream& in, void **data)
{
    Mesh *mesh = new Mesh();
    std::vector<float>::size_type posSize = 0, normSize = 0, texSize = 0;
    std::vector<unsigned int>::size_type indSize = 0;

    in.read((char *)&posSize, sizeof(std::vector<float>::size_type));
    in.read((char *)&normSize, sizeof(std::vector<float>::size_type));
    in.read((char *)&texSize, sizeof(std::vector<float>::size_type));
    in.read((char *)&indSize, sizeof(std::vector<unsigned int>::size_type));

    mesh->positions.resize(posSize);
    mesh->normals.resize(normSize);
    mesh->texcoords.resize(texSize);
    mesh->indices.resize(indSize);

    if (posSize > 0)
        in.read((char *)mesh->positions.data(),
        mesh->positions.size() * sizeof(float));
    if (normSize > 0)
        in.read((char *)mesh->normals.data(),
        mesh->normals.size() * sizeof(float));
    if (texSize > 0)
        in.read((char *)mesh->texcoords.data(),
        mesh->texcoords.size() * sizeof(float));
    if (indSize > 0)
        in.read((char *)mesh->indices.data(),
        mesh->indices.size() * sizeof(unsigned int));

    *data = mesh;

    return true;
}

bool MeshResource::saveData(std::ostream& out, const void *data)
{
    const Mesh *mesh = reinterpret_cast<const Mesh *>(data);

    std::vector<float>::size_type posSize = mesh->positions.size(),
        normSize = mesh->normals.size(),
        texSize = mesh->texcoords.size();
    std::vector<unsigned int>::size_type indSize = mesh->indices.size();

    out.write((char *)&posSize,
        sizeof(std::vector<float>::size_type));
    out.write((char *)&normSize,
        sizeof(std::vector<float>::size_type));
    out.write((char *)&texSize,
        sizeof(std::vector<float>::size_type));
    out.write((char *)&indSize,
        sizeof(std::vector<unsigned int>::size_type));

    out.write((char *)mesh->positions.data(),
        mesh->positions.size() * sizeof(float));
    out.write((char *)mesh->normals.data(),
        mesh->normals.size() * sizeof(float));
    out.write((char *)mesh->texcoords.data(),
        mesh->texcoords.size() * sizeof(float));
    out.write((char *)mesh->indices.data(),
        mesh->indices.size() * sizeof(unsigned int));

    return true;
}
