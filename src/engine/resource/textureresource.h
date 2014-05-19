#ifndef TEXTURERESOURCE_H
#define TEXTURERESOURCE_H

#include "../resource.h"
#include "../texture.h"

class TextureResource : public Resource<Texture>
{
public:
    bool loadData(std::istream& in, void **data);
    bool saveData(std::ostream& out, const void *data);

};

#endif
