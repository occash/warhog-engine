#ifndef MODULEINSPECTOR_H
#define MODULEINSPECTOR_H

#include <QWidget>
#include <QFormLayout>
#include <QMetaProperty>

class BaseModule;

class ModuleInspector : public QWidget
{
    Q_OBJECT

public:
    ModuleInspector(QWidget *parent = 0);
    ~ModuleInspector();

signals:
    void changed();

public slots:
    void inspectModule(QObject *);

private slots:
    void onBoolChanged(bool b);
    void onIntChanged(int i);
    void onDoubleChanged(double val);
    void onEnumChanged(const QString&);

private:
    void clearLayout();
    QWidget *setupBool(QObject *, QMetaProperty);
    QWidget *setupInt(QObject *, QMetaProperty);
    QWidget *setupDouble(QObject *, QMetaProperty);
    QWidget *setupEnum(QObject *, QMetaProperty);

private:
    QFormLayout *_layout;
    QMap<QWidget *, QMetaProperty> _props;
    QObject *_module;

};

#endif // MODULEINSPECTOR_H
