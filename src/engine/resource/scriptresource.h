#ifndef SCRIPTRESOURCE_H
#define SCRIPTRESOURCE_H

#include "../resource.h"
#include "../script.h"

class ENGINE_EXPORT ScriptResource : public Resource<Script>
{
public:
    bool loadData(std::istream& in, void **data);
    bool saveData(std::ostream& out, const void *data);
};

#endif
