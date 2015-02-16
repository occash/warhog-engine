#ifndef SELECTMODULE_H
#define SELECTMODULE_H

#include "basemodule.h"

class SelectModule : public BaseModule
{
    Q_OBJECT
    Q_PROPERTY(qreal EdgeFalloff READ getEdgeFalloff WRITE setEdgeFalloff)
    Q_PROPERTY(qreal LowerBound READ getLowerBound WRITE setLowerBound)
    Q_PROPERTY(qreal UpperBound READ getUpperBound WRITE setUpperBound)

public:
    SelectModule(QObject *parent = nullptr);
    ~SelectModule();

    qreal getEdgeFalloff() const;
    void setEdgeFalloff(qreal f);

    qreal getLowerBound() const;
    void setLowerBound(qreal f);

    qreal getUpperBound() const;
    void setUpperBound(qreal f);

private:

};

#endif // SELECTMODULE_H
