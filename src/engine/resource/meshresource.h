#ifndef MESHRESOURCE_H
#define MESHRESOURCE_H

#include "../global.h"
#include "../resource.h"
#include "../mesh.h"

class Renderer;

class ENGINE_EXPORT MeshResource : public Resource<Mesh>
{
public:
	MeshResource(Renderer *renderer);

	bool load(std::istream& in, Object *&resource) const override;
	bool save(std::ostream& out, Object *resource) const override;

private:
	Renderer *_renderer;

};

#endif
