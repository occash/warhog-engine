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
        mesh->positions = shapes[0].mesh.positions;
        mesh->normals = shapes[0].mesh.normals;
        mesh->texcoords = shapes[0].mesh.texcoords;
        mesh->indices = shapes[0].mesh.indices;

		return mesh;

        emit progress(100);
    }
}

QStringList MeshImporter::suffixes()
{
    return QStringList() << "obj";
}

QStringList MeshImporter::signatures()
{
    return QStringList();
}
