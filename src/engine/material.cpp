#include "material.h"

const char *Material::shader() const
{
	return _shader.c_str();
}

void Material::setShader(const char *name)
{
	_shader = name;
	createProgram(name);
}

void Material::bind()
{
}

void Material::unbind()
{
}

/*int Material::propertyCount() const
{
	return 0;
}

const char *Material::propertyName() const
{
	return nullptr;
}*/

Any Material::property(const char *name) const
{
	return Any();
}

void Material::setProperty(const char *name, const Any& value)
{
}

void Material::createProgram(const char *name)
{
}
