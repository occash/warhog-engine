#include "perlinmodule.h"

#include <noise/module/perlin.h>
#include <noise/noisegen.h>

#include <QVariant>
#include <QSizeF>

PerlinModule::PerlinModule(QObject *parent)
    : BaseModule("Perlin", new noise::module::Perlin(), parent)
{
    _quality.insert("Fast", noise::QUALITY_FAST);
    _quality.insert("Standard", noise::QUALITY_STD);
    _quality.insert("Best", noise::QUALITY_BEST);

    setProperty("FrequencyRange", QSizeF(0.0, 300.0));
    setProperty("LacunarityRange", QSizeF(1.5, 3.5));
    setProperty("NoiseQualityRange", QStringList() << "Fast" << "Standard" << "Best");
    setProperty("OctaveCountRange", QSize(1, noise::module::PERLIN_MAX_OCTAVE));
    setProperty("PersistenceRange", QSizeF(0.0, 1.0));
    setProperty("SeedRange", QSize(std::numeric_limits<int>::min(), std::numeric_limits<int>::max()));
}

PerlinModule::~PerlinModule()
{
}

qreal PerlinModule::getFrequency() const
{
    return static_cast<noise::module::Perlin *>(module())->GetFrequency();
}

void PerlinModule::setFrequency(qreal f)
{
    static_cast<noise::module::Perlin *>(module())->SetFrequency(f);
}

qreal PerlinModule::getLacunarity() const
{
    return static_cast<noise::module::Perlin *>(module())->GetLacunarity();
}

void PerlinModule::setLacunarity(qreal f)
{
    static_cast<noise::module::Perlin *>(module())->SetLacunarity(f);
}

QString PerlinModule::getNoiseQuality() const
{
    int q = static_cast<noise::module::Perlin *>(module())->GetNoiseQuality();
    return _quality.key(q, "Standard");
}

void PerlinModule::setNoiseQuality(QString s)
{
    int q = _quality.value(s, noise::QUALITY_STD);
    static_cast<noise::module::Perlin *>(module())->SetNoiseQuality((noise::NoiseQuality)q);
}

int PerlinModule::getOctaveCount() const
{
    return static_cast<noise::module::Perlin *>(module())->GetOctaveCount();
}

void PerlinModule::setOctaveCount(int f)
{
    static_cast<noise::module::Perlin *>(module())->SetOctaveCount(f);
}

qreal PerlinModule::getPersistence() const
{
    return static_cast<noise::module::Perlin *>(module())->GetPersistence();
}

void PerlinModule::setPersistence(qreal f)
{
    static_cast<noise::module::Perlin *>(module())->SetPersistence(f);
}

int PerlinModule::getSeed() const
{
    return static_cast<noise::module::Perlin *>(module())->GetSeed();
}

void PerlinModule::setSeed(int f)
{
    static_cast<noise::module::Perlin *>(module())->SetSeed(f);
}
