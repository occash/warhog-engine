#include "meshimporter.h"
#include "mesh.h"
#include "resource/meshresource.h"
#include "resourcemanager.h"

#include <QDir>
#include <tiny_obj_loader.h>
#include <fstream>

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
    QByteArray namebytes = filename.toLocal8Bit();
    const char *name = namebytes.constData();
    std::vector<tinyobj::shape_t> shapes;
    std::string err = tinyobj::LoadObj(shapes, name);
    if (err.length() > 0)
    {
        emit error(QString("Could not load mesh (") + name + "): " + err.c_str());
    }
    else
    {
        emit progress(50);

		std::shared_ptr<Mesh> mesh(new Mesh());
		for (int i = 0; i < shapes[0].mesh.positions.size(); ++i)
		{
			Vertex vertex;
			vertex.position[0] = shapes[0].mesh.positions[i];
			vertex.position[1] = shapes[0].mesh.positions[i + 1];
			vertex.position[2] = shapes[0].mesh.positions[i + 2];
			vertex.normal[0] = shapes[0].mesh.normals[i];
			vertex.normal[1] = shapes[0].mesh.normals[i + 1];
			vertex.normal[2] = shapes[0].mesh.normals[i + 2];
			vertex.normal[3] = 0;
			vertex.uv[0] = shapes[0].mesh.texcoords[i];
			vertex.uv[1] = shapes[0].mesh.texcoords[i + 1];
		}
        mesh->indices = shapes[0].mesh.indices;

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
