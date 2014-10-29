#include "selectmodule.h"

#include <QVariant>
#include <QSizeF>

SelectModule::SelectModule(QObject *parent)
    : BaseModule("Select", new noise::module::Select(), parent)
{
    setProperty("EdgeFalloffRange", QSizeF(0.0, 1.0));
    setProperty("LowerBoundRange", QSizeF(-1.0, 1.0));
    setProperty("UpperBoundRange", QSizeF(-1.0, 1.0));
}

SelectModule::~SelectModule()
{
}

qreal SelectModule::getEdgeFalloff() const
{
    return static_cast<noise::module::Select *>(module())->GetEdgeFalloff();
}

void SelectModule::setEdgeFalloff(qreal f)
{
    static_cast<noise::module::Select *>(module())->SetEdgeFalloff(f);
}

qreal SelectModule::getLowerBound() const
{
    return static_cast<noise::module::Select *>(module())->GetLowerBound();
}

void SelectModule::setLowerBound(qreal f)
{
    qreal upperBound = getUpperBound();
    static_cast<noise::module::Select *>(module())->SetBounds(f, upperBound);
}

qreal SelectModule::getUpperBound() const
{
    return static_cast<noise::module::Select *>(module())->GetUpperBound();
}

void SelectModule::setUpperBound(qreal f)
{
    qreal lowerBound = getLowerBound();
    static_cast<noise::module::Select *>(module())->SetBounds(lowerBound, f);
}
