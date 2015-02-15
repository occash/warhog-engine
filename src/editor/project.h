#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>

class Project : public QObject
{
    Q_OBJECT

public:
    QString path() const;
    QString projectPath() const;
    QString version() const;
    QString name() const;
    QString resources() const;
    QString scene() const;

    static Project *open(const QString& path);
    static QString create(const QString& path, const QString& name);

private:
    Project(const QString& path);

    void setVersion(const QString& v);
    void setName(const QString& v);
    void setResources(const QString& v);
    void setScene(const QString& v);

private:
    QString _path;
    QString _projectPath;
    QString _version;
    QString _name;
    QString _resources;
    QString _scene;

};

#endif