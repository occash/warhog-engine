#ifndef VORONOIMODULE_H
#define VORONOIMODULE_H

#include "basemodule.h"

class VoronoiModule : public BaseModule
{
    Q_OBJECT
    Q_PROPERTY(qreal Displacement READ getDisplacement WRITE setDisplacement)
    Q_PROPERTY(bool EnableDistance READ isDistanceEnabled WRITE enableDistance)
    Q_PROPERTY(qreal Frequency READ getFrequency WRITE setFrequency)
    Q_PROPERTY(int Seed READ getSeed WRITE setSeed)

public:
    VoronoiModule(QObject *parent = nullptr);
    ~VoronoiModule();

    qreal getDisplacement() const;
    void setDisplacement(qreal d);

    bool isDistanceEnabled() const;
    void enableDistance(bool e);

    qreal getFrequency() const;
    void setFrequency(qreal d);

    int getSeed() const;
    void setSeed(int i);

};

#endif // VORONOIMODULE_H
