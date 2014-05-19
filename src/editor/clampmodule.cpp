#include "clampmodule.h"

#include <QVariant>
#include <QSizeF>

ClampModule::ClampModule(QObject *parent)
: BaseModule("Clamp", new noise::module::Clamp(), parent)
{
    setProperty("LowerBoundRange", QSizeF(-1.0, 1.0));
    setProperty("UpperBoundRange", QSizeF(-1.0, 1.0));
}

ClampModule::~ClampModule()
{
}

qreal ClampModule::getLowerBound() const
{
    return static_cast<noise::module::Clamp *>(module())->GetLowerBound();
}

void ClampModule::setLowerBound(qreal f)
{
    qreal upperBound = getUpperBound();
    static_cast<noise::module::Clamp *>(module())->SetBounds(f, upperBound);
}

qreal ClampModule::getUpperBound() const
{
    return static_cast<noise::module::Clamp *>(module())->GetUpperBound();
}

void ClampModule::setUpperBound(qreal f)
{
    qreal lowerBound = getLowerBound();
    static_cast<noise::module::Clamp *>(module())->SetBounds(lowerBound, f);
}
