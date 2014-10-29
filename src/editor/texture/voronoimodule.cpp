#include "voronoimodule.h"

#include <noise/module/voronoi.h>

#include <QVariant>
#include <QSizeF>

VoronoiModule::VoronoiModule(QObject *parent)
    : BaseModule("Voronoi", new noise::module::Voronoi(), parent)
{
    setProperty("DisplacementRange", QSizeF(0.0, 1.0));
    setProperty("FrequencyRange", QSizeF(0.0, 300.0));
    setProperty("SeedRange", QSize(std::numeric_limits<int>::min(), std::numeric_limits<int>::max()));
}

VoronoiModule::~VoronoiModule()
{
}

qreal VoronoiModule::getDisplacement() const
{
    return static_cast<noise::module::Voronoi *>(module())->GetDisplacement();
}

void VoronoiModule::setDisplacement(qreal d)
{
    static_cast<noise::module::Voronoi *>(module())->SetDisplacement(d);
}

bool VoronoiModule::isDistanceEnabled() const
{
    return static_cast<noise::module::Voronoi *>(module())->IsDistanceEnabled();
}

void VoronoiModule::enableDistance(bool e)
{
    static_cast<noise::module::Voronoi *>(module())->EnableDistance(e);
}

qreal VoronoiModule::getFrequency() const
{
    return static_cast<noise::module::Voronoi *>(module())->GetFrequency();
}

void VoronoiModule::setFrequency(qreal d)
{
    static_cast<noise::module::Voronoi *>(module())->SetFrequency(d);
}

int VoronoiModule::getSeed() const
{
    return static_cast<noise::module::Voronoi *>(module())->GetSeed();
}

void VoronoiModule::setSeed(int i)
{
    static_cast<noise::module::Voronoi *>(module())->SetSeed(i);
}
