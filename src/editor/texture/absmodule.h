#ifndef ABSMODULE_H
#define ABSMODULE_H

#include "basemodule.h"

class AbsModule : public BaseModule
{
    Q_OBJECT

public:
    AbsModule(QObject *parent = nullptr);
    ~AbsModule();

private:

};

#endif // ABSMODULE_H
