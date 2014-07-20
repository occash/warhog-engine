#ifndef SCRIPTIMPORTER_H
#define SCRIPTIMPORTER_H

#include "importer.h"

#include <QMap>

class ScriptImporter : public Importer
{
    Q_OBJECT

public:
    ScriptImporter(QObject *parent = nullptr);
    ~ScriptImporter();

    std::shared_ptr<Object> import(const QString& filename, const QVariantMap& config = QVariantMap());
    QStringList suffixes();
    QStringList signatures();

private:
    QMap<QString, QString> _engineMap;

};

#endif // SCRIPTIMPORTER_H
