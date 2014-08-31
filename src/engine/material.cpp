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
