#ifndef TEXTURERESOURCE_H
#define TEXTURERESOURCE_H

#include "../resource.h"
#include "../texture.h"

class Renderer;

class ENGINE_EXPORT TextureResource : public Resource<Texture>
{
public:
	TextureResource(Renderer *renderer);
	~TextureResource();

	bool load(std::istream& in, Object *&resource) const override;
	bool save(std::ostream& out, Object *resource) const override;

private:
	Renderer *_renderer;

};

#endif
