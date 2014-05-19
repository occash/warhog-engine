#ifndef MESHIMPORTER_H
#define MESHIMPORTER_H

#include "importer.h"

class MeshImporter : public Importer
{
    Q_OBJECT

public:
    MeshImporter(QObject *parent = nullptr);
    ~MeshImporter();

    void import(const QString& filename);
    QStringList suffixes();
    QStringList signatures();

};

#endif // MESHIMPORTER_H
