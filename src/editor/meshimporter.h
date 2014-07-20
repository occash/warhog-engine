#ifndef MESHIMPORTER_H
#define MESHIMPORTER_H

#include "importer.h"

class MeshImporter : public Importer
{
    Q_OBJECT

public:
    MeshImporter(QObject *parent = nullptr);
    ~MeshImporter();

    std::shared_ptr<Object> import(const QString& filename, const QVariantMap& config = QVariantMap());
    QStringList suffixes();
    QStringList signatures();

};

#endif // MESHIMPORTER_H
