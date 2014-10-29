#include "constmodule.h"

#include <QVariant>
#include <QSizeF>

ConstModule::ConstModule(QObject *parent)
    : BaseModule("Const", new noise::module::Const(), parent)
{
    setProperty("ConstValueRange", QSizeF(-1.0, 1.0));
}

ConstModule::~ConstModule()
{
}

qreal ConstModule::getConstValue() const
{
    return static_cast<noise::module::Const *>(module())->GetConstValue();
}

void ConstModule::setConstValue(qreal f)
{
    static_cast<noise::module::Const *>(module())->SetConstValue(f);
}
