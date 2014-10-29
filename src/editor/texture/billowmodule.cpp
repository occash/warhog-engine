#include "billowmodule.h"

#include <QVariant>
#include <QSizeF>

#include <noise/module/billow.h>

BillowModule::BillowModule(QObject *parent)
    : BaseModule("Billow", new noise::module::Billow(), parent)
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

BillowModule::~BillowModule()
{

}

qreal BillowModule::getFrequency() const
{
    return static_cast<noise::module::Perlin *>(module())->GetFrequency();
}

void BillowModule::setFrequency(qreal f)
{
    static_cast<noise::module::Perlin *>(module())->SetFrequency(f);
}

qreal BillowModule::getLacunarity() const
{
    return static_cast<noise::module::Perlin *>(module())->GetLacunarity();
}

void BillowModule::setLacunarity(qreal f)
{
    static_cast<noise::module::Perlin *>(module())->SetLacunarity(f);
}

QString BillowModule::getNoiseQuality() const
{
    int q = static_cast<noise::module::Perlin *>(module())->GetNoiseQuality();
    return _quality.key(q, "Standard");
}

void BillowModule::setNoiseQuality(QString s)
{
    int q = _quality.value(s, noise::QUALITY_STD);
    static_cast<noise::module::Perlin *>(module())->SetNoiseQuality((noise::NoiseQuality)q);
}

int BillowModule::getOctaveCount() const
{
    return static_cast<noise::module::Perlin *>(module())->GetOctaveCount();
}

void BillowModule::setOctaveCount(int f)
{
    static_cast<noise::module::Perlin *>(module())->SetOctaveCount(f);
}

qreal BillowModule::getPersistence() const
{
    return static_cast<noise::module::Perlin *>(module())->GetPersistence();
}

void BillowModule::setPersistence(qreal f)
{
    static_cast<noise::module::Perlin *>(module())->SetPersistence(f);
}

int BillowModule::getSeed() const
{
    return static_cast<noise::module::Perlin *>(module())->GetSeed();
}

void BillowModule::setSeed(int f)
{
    static_cast<noise::module::Perlin *>(module())->SetSeed(f);
}