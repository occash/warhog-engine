#ifndef MESHRESOURCE_H
#define MESHRESOURCE_H

#include "../global.h"
#include "../resource.h"
#include "../mesh.h"

class ENGINE_EXPORT MeshResource : public Resource<Mesh>
{
public:
    bool loadData(std::istream& in, void **data);
    bool saveData(std::ostream& out, const void *data);

};

#endif
