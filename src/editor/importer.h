#ifndef IMPORTER_H
#define IMPORTER_H

#include <QObject>
#include <QStringList>
#include <QVariantMap>

#include <memory>
#include <object.h>

class Importer : public QObject
{
    Q_OBJECT

public:
    Importer(QObject *parent = nullptr);
    ~Importer();

    virtual std::shared_ptr<Object> import(const QString& filename, const QVariantMap& config = QVariantMap()) = 0;
    virtual QStringList suffixes() = 0;
    virtual QStringList signatures() = 0;

signals:
    void error(QString e);
    void progress(int p);

};

#endif // IMPORTER_H
