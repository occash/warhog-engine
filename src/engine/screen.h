#ifndef MONITOR_H
#define MONITOR_H

#include "global.h"

class ENGINE_EXPORT Screen
{
public:
    ~Screen();

    static Screen *primary();
    static int screenCount();
    static Screen *screen(int);

private:
    Screen();

};

#endif
