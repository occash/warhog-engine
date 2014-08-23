#ifndef MATERIALCOMPONENT_H
#define MATERIALCOMPONENT_H

#include "../global.h"
#include <entityx/Entity.h>

using namespace entityx;
class Material;

class ENGINE_EXPORT MaterialComponent : public Component<MaterialComponent>
{
public:
    MaterialComponent();
    ~MaterialComponent();

	Material *material() const;
	void setMaterial(Material *);

private:
	Material *_material;

};

#endif
