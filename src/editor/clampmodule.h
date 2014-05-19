#ifndef CLAMPMODULE_H
#define CLAMPMODULE_H

#include "basemodule.h"

class ClampModule : public BaseModule
{
    Q_OBJECT

    Q_PROPERTY(qreal LowerBound READ getLowerBound WRITE setLowerBound)
    Q_PROPERTY(qreal UpperBound READ getUpperBound WRITE setUpperBound)

public:
    ClampModule(QObject *parent = nullptr);
    ~ClampModule();

    qreal getLowerBound() const;
    void setLowerBound(qreal f);

    qreal getUpperBound() const;
    void setUpperBound(qreal f);

private:
    noise::module::Clamp *_clamp;

};

#endif // CLAMPMODULE_H
