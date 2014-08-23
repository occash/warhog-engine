#ifndef SCRIPT_H
#define SCRIPT_H

#include "global.h"
#include "meta/object.h"

#include <string>

class ENGINE_EXPORT Script : public Object
{
	OBJECT(Script, Object)
public:
    Script();
    ~Script();

    std::string engine;
    std::string name;
    std::string source;
};

#endif
