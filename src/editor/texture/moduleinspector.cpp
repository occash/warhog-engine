#include "moduleinspector.h"
#include "basemodule.h"

#include <QObject>
#include <QCheckBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>


ModuleInspector::ModuleInspector(QWidget *parent)
    : QWidget(parent),
      _layout(new QFormLayout(this))
{
    setLayout(_layout);
}

ModuleInspector::~ModuleInspector()
{

}

void ModuleInspector::inspectModule(QObject *module)
{
    clearLayout();

    if (!module)
        return;

    //Setup properties
    const QMetaObject *moduleMeta = module->metaObject();
    for (int i = 1; i < moduleMeta->propertyCount(); ++i)
    {
        QMetaProperty prop = moduleMeta->property(i);
        QString pname = prop.name();
        QStringList plist = pname.split(QRegExp("(?=[A-Z])"), QString::SkipEmptyParts);
        pname = plist[0];
        for (int i = 1; i < plist.size(); ++i)
        {
            pname.append(" ");
            pname.append(plist[i]);
        }

        QWidget *editor = nullptr;
        if (prop.type() == QVariant::Bool)
            editor = setupBool(module, prop);
        if (prop.type() == QVariant::Int)
            editor = setupInt(module, prop);
        if (prop.type() == QVariant::Double)
            editor = setupDouble(module, prop);
        if (prop.type() == QVariant::String)
            editor = setupEnum(module, prop);

        if (editor)
        {
            _props.insert(editor, prop);
            _layout->addRow(pname, editor);
        }
    }

    _module = module;
}

QWidget *ModuleInspector::setupBool(QObject *meta, QMetaProperty prop)
{
    QCheckBox *box = new QCheckBox();
    box->setChecked(prop.read(meta).toBool());
    connect(box, SIGNAL(toggled(bool)), this, SLOT(onBoolChanged(bool)));
    return box;
}

QWidget *ModuleInspector::setupInt(QObject *meta, QMetaProperty prop)
{
    QSpinBox *slider = new QSpinBox();
    slider->setValue(prop.read(meta).toInt());
    QVariant vrange = meta->property((QString(prop.name()) + "Range").toLatin1().constData());
    if (vrange.type() == QVariant::Size)
    {
        QSize range = vrange.toSize();
        slider->setMinimum(range.width());
        slider->setMaximum(range.height());
        slider->setSingleStep(1);
    }
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(onIntChanged(int)));
    return slider;
}

QWidget *ModuleInspector::setupDouble(QObject *meta, QMetaProperty prop)
{
    QDoubleSpinBox *slider = new QDoubleSpinBox();
    slider->setValue(prop.read(meta).toDouble());
    QVariant vrange = meta->property((QString(prop.name()) + "Range").toLatin1().constData());
    if (vrange.type() == QVariant::SizeF)
    {
        QSizeF range = vrange.toSizeF();
        slider->setMinimum(range.width());
        slider->setMaximum(range.height());
        slider->setSingleStep((range.height() - range.width()) / 1000.0);
    }
    connect(slider, SIGNAL(valueChanged(double)), this, SLOT(onDoubleChanged(double)));
    return slider;
}

QWidget *ModuleInspector::setupEnum(QObject *meta, QMetaProperty prop)
{
    QComboBox *box = new QComboBox();
    QVariant vrange = meta->property((QString(prop.name()) + "Range").toLatin1().constData());
    if (vrange.type() == QVariant::StringList)
    {
        QStringList range = vrange.toStringList();
        box->addItems(range);
    }
    box->setCurrentText(prop.read(meta).toString());
    connect(box, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(onEnumChanged(const QString&)));
    return box;
}

void ModuleInspector::onBoolChanged(bool b)
{
    QCheckBox *slider = qobject_cast<QCheckBox *>(sender());
    auto prop = _props.find(slider);
    if (prop != _props.end())
    {
        if ((*prop).write(_module, b))
            emit changed();
    }
}

void ModuleInspector::onIntChanged(int i)
{
    QSpinBox *slider = qobject_cast<QSpinBox *>(sender());
    auto prop = _props.find(slider);
    if (prop != _props.end())
    {
        if ((*prop).write(_module, i))
            emit changed();
    }
}

void ModuleInspector::onDoubleChanged(double d)
{
    QDoubleSpinBox *slider = qobject_cast<QDoubleSpinBox *>(sender());
    auto prop = _props.find(slider);
    if (prop != _props.end())
    {
        if ((*prop).write(_module, d))
            emit changed();
    }
}

void ModuleInspector::onEnumChanged(const QString& e)
{
    QComboBox *slider = qobject_cast<QComboBox *>(sender());
    auto prop = _props.find(slider);
    if (prop != _props.end())
    {
        if ((*prop).write(_module, e))
            emit changed();
    }
}

void ModuleInspector::clearLayout()
{
    _props.clear();

    if (!layout())
        return;

    while (!layout()->isEmpty())
    {
        QLayoutItem *item = layout()->takeAt(0);
        delete item->widget();
        delete item;
    }
}
