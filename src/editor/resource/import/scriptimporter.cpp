#include "scriptimporter.h"
#include <script.h>
#include <resource/scriptresource.h>
#include <resourcemanager.h>

#include <QFile>

ScriptImporter::ScriptImporter(QObject *parent)
    : Importer(parent)
{
    _engineMap.insert("lua", "lua");
    _engineMap.insert("py", "python");
}

ScriptImporter::~ScriptImporter()
{

}

std::shared_ptr<Object> ScriptImporter::import(const QString& filename, const QVariantMap& config /*= QVariantMap()*/)
{
    int sep = filename.lastIndexOf('/');
    QString shortName = filename.mid(sep + 1);
    QStringList nameExt = shortName.split('.');

    if (!_engineMap.contains(nameExt[1]))
        return std::shared_ptr<Object>();

    QByteArray engineBytes = _engineMap[nameExt[1]].toLocal8Bit();
    QByteArray nameBytes = nameExt[0].toLocal8Bit();
    QFile srcFile(filename);
    srcFile.open(QIODevice::ReadOnly);
    QByteArray sourceBytes = srcFile.readAll();

    std::shared_ptr<Script> script(new Script());
    script->engine = engineBytes.constData();
    script->name = nameBytes.constData();
    script->source = sourceBytes.constData();

	return script;
}

QStringList ScriptImporter::suffixes()
{
    return QStringList() << "lua" << "py";
}
