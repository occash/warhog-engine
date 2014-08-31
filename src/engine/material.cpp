#include "material.h"
#include "shader.h"

Material::Material() :
	_shader(nullptr),
	_material(nullptr)
{
}

Material::~Material()
{
}

Shader *Material::shader() const
{
	return _shader;
}

void Material::setShader(Shader *shader)
{
	_shader = shader;
	_material = _shader->block("Material");
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
	ShaderVariable *var = _material->variable(name);
	return var->get();
}

void Material::setProperty(const char *name, const Any& value)
{
	ShaderVariable *var = _material->variable(name);
	var->set(value);
}
