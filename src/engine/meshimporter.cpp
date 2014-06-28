#include "meshimporter.h"
/*#include "mesh.h"

#include <tiny_obj_loader.h>
#include <iostream>
#include <fstream>

MeshImporter::MeshImporter()
{
}


MeshImporter::~MeshImporter()
{
}

Mesh *MeshImporter::import(const std::string& name)
{
    return nullptr;
	std::vector<tinyobj::shape_t> shapes;
	std::string error = tinyobj::LoadObj(shapes, name.c_str(), "models/");
	if (error.length() > 0)
	{
		std::cout << "Could not load mesh (" + name + "): " << error << std::endl;
		return nullptr;
	}
	else
	{
		Mesh *mesh = new Mesh();
		mesh->_mesh = shapes[0].mesh;
		return mesh;
	}
}

Mesh * MeshImporter::load(const std::string& name)
{
    return nullptr;
    std::ifstream file(name, std::ios::binary);
    Mesh *mesh = new Mesh();
	std::vector<float>::size_type posSize = 0, normSize = 0, texSize = 0;
	std::vector<unsigned int>::size_type indSize = 0;
    
    file.read((char *)&posSize, sizeof(std::vector<float>::size_type));
    file.read((char *)&normSize, sizeof(std::vector<float>::size_type));
    file.read((char *)&texSize, sizeof(std::vector<float>::size_type));
    file.read((char *)&indSize, sizeof(std::vector<unsigned int>::size_type));

    mesh->_mesh.positions.resize(posSize);
    mesh->_mesh.normals.resize(normSize);
    mesh->_mesh.texcoords.resize(texSize);
    mesh->_mesh.indices.resize(indSize);

    if (posSize > 0)
        file.read((char *)mesh->_mesh.positions.data(),
        mesh->_mesh.positions.size() * sizeof(float));
    if (normSize > 0)
        file.read((char *)mesh->_mesh.normals.data(),
        mesh->_mesh.normals.size() * sizeof(float));
    if (texSize > 0)
        file.read((char *)mesh->_mesh.texcoords.data(),
        mesh->_mesh.texcoords.size() * sizeof(float));
    if (indSize > 0)
        file.read((char *)mesh->_mesh.indices.data(),
        mesh->_mesh.indices.size() * sizeof(unsigned int));

    return mesh;
}

void MeshImporter::save(const std::string& name, Mesh *mesh)
{
    std::ofstream file(name, std::ios::binary);
    std::vector<float>::size_type posSize = mesh->_mesh.positions.size(), 
        normSize = mesh->_mesh.normals.size(), 
        texSize = mesh->_mesh.texcoords.size();
    std::vector<unsigned int>::size_type indSize = mesh->_mesh.indices.size();

    file.write((char *)&posSize,
        sizeof(std::vector<float>::size_type));
    file.write((char *)&normSize,
        sizeof(std::vector<float>::size_type));
    file.write((char *)&texSize,
        sizeof(std::vector<float>::size_type));
    file.write((char *)&indSize,
        sizeof(std::vector<unsigned int>::size_type));

    file.write((char *)mesh->_mesh.positions.data(),
        mesh->_mesh.positions.size() * sizeof(float));
    file.write((char *)mesh->_mesh.normals.data(),
        mesh->_mesh.normals.size() * sizeof(float));
    file.write((char *)mesh->_mesh.texcoords.data(),
        mesh->_mesh.texcoords.size() * sizeof(float));
    file.write((char *)mesh->_mesh.indices.data(),
        mesh->_mesh.indices.size() * sizeof(unsigned int));
}*/
