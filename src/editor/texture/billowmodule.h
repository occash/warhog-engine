#ifndef BILLOWMODULE_H
#define BILLOWMODULE_H

#include <QMap>

#include "basemodule.h"

class BillowModule : public BaseModule
{
    Q_OBJECT
    Q_PROPERTY(qreal Frequency READ getFrequency WRITE setFrequency)
    Q_PROPERTY(qreal Lacunarity READ getLacunarity WRITE setLacunarity)
    Q_PROPERTY(QString NoiseQuality READ getNoiseQuality WRITE setNoiseQuality)
    Q_PROPERTY(int OctaveCount READ getOctaveCount WRITE setOctaveCount)
    Q_PROPERTY(qreal Persistence READ getPersistence WRITE setPersistence)
    Q_PROPERTY(int Seed READ getSeed WRITE setSeed)

public:
    BillowModule(QObject *parent = nullptr);
    ~BillowModule();

    qreal getFrequency() const;
    void setFrequency(qreal f);

    qreal getLacunarity() const;
    void setLacunarity(qreal f);

    QString getNoiseQuality() const;
    void setNoiseQuality(QString s);

    int getOctaveCount() const;
    void setOctaveCount(int f);

    qreal getPersistence() const;
    void setPersistence(qreal f);

    int getSeed() const;
    void setSeed(int f);

private:
    QMap<QString, int> _quality;

};

#endif // BILLOWMODULE_H
