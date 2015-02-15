#ifndef BASEMODULE_H
#define BASEMODULE_H

#include <QObject>
#include <QVector>

#include <noise/module/module.h>
#include <noise/module/perlin.h>
#include <noise/module/clamp.h>


class BaseModule : public QObject
{
    Q_OBJECT

public:
    BaseModule(QString name, noise::module::Module *module, QObject *parent = nullptr);
    ~BaseModule();

    BaseModule *source(int id) const;
    void setSource(int id, BaseModule *source);
    bool isValid() const;

    QString name() const;
    noise::module::Module *module() const;

private:
    QString _name;
    noise::module::Module *_module;
    QVector<BaseModule *> _sources;

};

#endif // BASEMODULE_H
