#ifndef IMPORTER_H
#define IMPORTER_H

#include <QObject>
#include <QStringList>

class Importer : public QObject
{
    Q_OBJECT

public:
    Importer(QObject *parent = nullptr);
    ~Importer();

    virtual void import(const QString& filename) = 0;
    virtual QStringList suffixes() = 0;
    virtual QStringList signatures() = 0;

signals:
    void error(QString e);
    void progress(int p);

};

#endif // IMPORTER_H
