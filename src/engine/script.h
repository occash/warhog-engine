#ifndef SCRIPT_H
#define SCRIPT_H

#include "global.h"

#include <string>

class ENGINE_EXPORT Script
{
public:
    Script();
    ~Script();

    std::string engine;
    std::string name;
    std::string source;
};

#endif
