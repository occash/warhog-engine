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

    std::shared_ptr<Object> import(const QString& filename, const QVariantMap& config = QVariantMap());
    QStringList suffixes();
    QStringList signatures();

};

#endif // TEXTUREIMPORTER_H
