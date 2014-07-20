#ifndef TEXTURERESOURCE_H
#define TEXTURERESOURCE_H

#include "../resource.h"
#include "../texture.h"

class ENGINE_EXPORT TextureResource : public Resource<Texture>
{
public:
	bool load(std::istream& in, Object *&resource) const override;
	bool save(std::ostream& out, Object *resource) const override;

};

#endif
