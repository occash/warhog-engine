#include "materialcomponent.h"

MaterialComponent::MaterialComponent()
{

}

MaterialComponent::~MaterialComponent()
{

}

Material *MaterialComponent::material() const
{
	return _material;
}

void MaterialComponent::setMaterial(Material *material)
{
	_material = material;
}
