#ifndef TEXTUREIMPORTER_H
#define TEXTUREIMPORTER_H

#include "importer.h"

#include <QMap>

class TextureImporter : public Importer
{
    Q_OBJECT

public:
    TextureImporter(QObject *parent = nullptr);
    ~TextureImporter();

    void import(const QString& filename);
    QStringList suffixes();
    QStringList signatures();

};

#endif // TEXTUREIMPORTER_H
