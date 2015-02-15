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
    if (var)
        return var->get();

    return Any();
}

void Material::setProperty(const char *name, const Any& value)
{
    ShaderVariable *var = nullptr;
    if (_material)
        var = _material->variable(name);
    if (!var)
    {
        std::string globalName = "material_";
        globalName.append(name);
        var = _shader->variable(globalName.c_str());
    }

    if (var)
        var->set(value);
}
