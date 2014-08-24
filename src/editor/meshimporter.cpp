#include "meshimporter.h"
#include "mesh.h"
#include "resource/meshresource.h"
#include "resourcemanager.h"

#include <QDir>
//#include <tiny_obj_loader.h>
//#include <fstream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

unsigned char floatToChar(float value)
{
	//Scale and bias
	value = (value + 1.0f) * 0.5f;
	return (unsigned char)(value * 255.0f);
}

MeshImporter::MeshImporter(QObject *parent)
    : Importer(parent)
{
    //ResourceManager::add<MeshResource>();
}

MeshImporter::~MeshImporter()
{

}

std::shared_ptr<Object> MeshImporter::import(const QString& filename, const QVariantMap& config /*= QVariantMap()*/)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(filename.toStdString(),
		aiProcess_CalcTangentSpace |
		aiProcess_JoinIdenticalVertices |
		aiProcess_Triangulate |
		aiProcess_GenNormals);
    if (scene == nullptr)
        emit error(QString("Could not load mesh (") + filename + "): " + importer.GetErrorString());
    else
    {
		const aiMesh *importedMesh = scene->mMeshes[0];

        emit progress(50);

		std::shared_ptr<Mesh> mesh(new Mesh());
		mesh->verticies.resize(importedMesh->mNumVertices);
		for (int i = 0; i < importedMesh->mNumVertices; ++i)
		{
			Vertex vertex;
			vertex.position[0] = importedMesh->mVertices[i].x;
			vertex.position[1] = importedMesh->mVertices[i].y;
			vertex.position[2] = importedMesh->mVertices[i].z;
			vertex.normal[0] = floatToChar(importedMesh->mNormals[i].x);
			vertex.normal[1] = floatToChar(importedMesh->mNormals[i].y);
			vertex.normal[2] = floatToChar(importedMesh->mNormals[i].z);
			vertex.normal[3] = floatToChar(0.0f);
			//vertex.uv[0] = shapes[0].mesh.texcoords[i];
			//vertex.uv[1] = shapes[0].mesh.texcoords[i + 1];
			mesh->verticies[i] = vertex;
		}
        mesh->indices.resize(importedMesh->mNumFaces * 3);
		for (int i = 0; i < importedMesh->mNumFaces; ++i)
		{
			mesh->indices[i * 3] = importedMesh->mFaces[i].mIndices[0];
			mesh->indices[i * 3 + 1] = importedMesh->mFaces[i].mIndices[1];
			mesh->indices[i * 3 + 2] = importedMesh->mFaces[i].mIndices[2];
		}

		emit progress(100);

		return mesh;
    }

	return std::shared_ptr<Mesh>();
}

QStringList MeshImporter::suffixes()
{
    return QStringList() << "obj";
}

QStringList MeshImporter::signatures()
{
    return QStringList();
}
