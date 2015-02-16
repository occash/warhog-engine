#include "meshimporter.h"
#include "mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/ProgressHandler.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class ProgressHandler : public Assimp::ProgressHandler
{
public:
    ProgressHandler(MeshImporter *importer) :
        _importer(importer) {}

    bool Update(float val) override
    {
        _importer->onUpdate(val);
        return true;
    }

private:
    MeshImporter *_importer;

};

unsigned char floatToChar(float value)
{
    //Scale and bias
    value = (value + 1.0f) * 0.5f;
    return (unsigned char)(value * 255.0f);
}

MeshImporter::MeshImporter(QObject *parent)
    : Importer(parent),
      _importer(new Assimp::Importer),
      _handler(new ProgressHandler(this))
{
    _importer->SetProgressHandler(_handler);
}

MeshImporter::~MeshImporter()
{

}

std::shared_ptr<Object> MeshImporter::import(const QString& filename, const QVariantMap& config /*= QVariantMap()*/)
{
    const aiScene *scene = _importer->ReadFile(
                               filename.toStdString(),
                               aiProcess_CalcTangentSpace |
                               aiProcess_JoinIdenticalVertices |
                               aiProcess_Triangulate |
                               aiProcess_GenNormals
                           );

    if (scene == nullptr)
        emit error(QString("Could not load mesh (") + filename + "): " + _importer->GetErrorString());
    else
    {
        const aiMesh *importedMesh = scene->mMeshes[0];

        std::shared_ptr<Mesh> mesh(new Mesh());
        mesh->verticies.resize(importedMesh->mNumVertices);
        emit info("Loading verticies");

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

            if (importedMesh->mTextureCoords[0])
            {
                vertex.uv[0] = importedMesh->mTextureCoords[0][i].x;
                vertex.uv[1] = importedMesh->mTextureCoords[0][i].y;
            }

            if (importedMesh->mTangents)
            {
                vertex.tangent[0] = floatToChar(importedMesh->mTangents[i].x);
                vertex.tangent[1] = floatToChar(importedMesh->mTangents[i].y);
                vertex.tangent[2] = floatToChar(importedMesh->mTangents[i].z);
                vertex.tangent[3] = floatToChar(0.0f);
            }

            mesh->verticies[i] = vertex;

            emit progress((i / importedMesh->mNumVertices) * 100);
        }

        mesh->indices.resize(importedMesh->mNumFaces * 3);
        emit info("Loading indices");

        for (int i = 0; i < importedMesh->mNumFaces; ++i)
        {
            int numInd = importedMesh->mFaces[i].mNumIndices;
            mesh->indices[i * 3] = importedMesh->mFaces[i].mIndices[0];
            mesh->indices[i * 3 + 1] = importedMesh->mFaces[i].mIndices[1];
            mesh->indices[i * 3 + 2] = importedMesh->mFaces[i].mIndices[2];

            emit progress(((float)i / importedMesh->mNumFaces) * 100);
        }

        _importer->FreeScene();
        emit success();

        return mesh;
    }

    return std::shared_ptr<Mesh>();
}

QStringList MeshImporter::suffixes()
{
    std::string exts;
    _importer->GetExtensionList(exts);
    QString qExts(QString::fromStdString(exts));
    QStringList extList = qExts.split(";*.");
    extList[0] = QString(extList[0]).mid(2);
    return extList;
}

void MeshImporter::onUpdate(float val)
{
    emit progress(int(val * 100));
}
