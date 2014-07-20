#ifndef MESHRESOURCE_H
#define MESHRESOURCE_H

#include "../global.h"
#include "../resource.h"
#include "../mesh.h"

class ENGINE_EXPORT MeshResource : public Resource<Mesh>
{
public:
	bool load(std::istream& in, Object *&resource) const override;
	bool save(std::ostream& out, Object *resource) const override;

};

#endif
