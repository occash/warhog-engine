#ifndef SCRIPTRESOURCE_H
#define SCRIPTRESOURCE_H

#include "../resource.h"
#include "../script.h"

class ENGINE_EXPORT ScriptResource : public Resource<Script>
{
public:
	bool load(std::istream& in, Object *&resource) const override;
	bool save(std::ostream& out, Object *resource) const override;

};

#endif
