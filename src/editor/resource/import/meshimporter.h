#ifndef MESHIMPORTER_H
#define MESHIMPORTER_H

#include "importer.h"

namespace Assimp
{
	class Importer;
	class ProgressHandler;
}

class ProgressHandler;

class MeshImporter : public Importer
{
    Q_OBJECT

public:
    MeshImporter(QObject *parent = nullptr);
    ~MeshImporter();

    std::shared_ptr<Object> import(const QString& filename, const QVariantMap& config = QVariantMap());
    QStringList suffixes();

private:
	void onUpdate(float val);

private:
	friend class ProgressHandler;
	Assimp::Importer *_importer;
	Assimp::ProgressHandler *_handler;

};

#endif // MESHIMPORTER_H
