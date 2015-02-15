#ifndef CONSTMODULE_H
#define CONSTMODULE_H

#include "basemodule.h"

class ConstModule : public BaseModule
{
    Q_OBJECT
    Q_PROPERTY(qreal ConstValue READ getConstValue WRITE setConstValue)

public:
    ConstModule(QObject *parent = nullptr);
    ~ConstModule();

    qreal getConstValue() const;
    void setConstValue(qreal f);

private:

};

#endif // CONSTMODULE_H
