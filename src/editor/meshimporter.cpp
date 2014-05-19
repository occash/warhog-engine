#include "meshimporter.h"
#include "mesh.h"
#include "meshresource.h"
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

void MeshImporter::import(const QString& filename)
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

        int sep = filename.lastIndexOf('/');
        QString shortName = filename.mid(sep + 1);
        int pnt = shortName.lastIndexOf('.');
        shortName = shortName.mid(0, pnt);
        QByteArray shortBytes = shortName.toLocal8Bit();

        ResourceManager::save(std::string("Meshes\\") + shortBytes.constData() + ".mesh", mesh);

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
