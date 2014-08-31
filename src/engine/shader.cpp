#include "shader.h"
#include "meta/any.h"

const char * ShaderVariable::name() const
{
	return nullptr;
}

Type ShaderVariable::type() const
{
	return Type(nullptr);
}

Any ShaderVariable::get() const
{
	return Any();
}

void ShaderVariable::set(const Any&)
{

}

const char * ShaderBlock::name() const
{
	return nullptr;
}

ShaderVariable * ShaderBlock::variable(const char *name) const
{
	return nullptr;
}

void ShaderBlock::get(void *, int)
{

}

void ShaderBlock::set(void *, int)
{

}

void Shader::bind()
{

}

void Shader::unbind()
{

}

void Shader::load()
{

}

void Shader::unload()
{

}

ShaderVariable * Shader::variable(const char *) const
{
	return nullptr;
}

ShaderBlock * Shader::block(const char *) const
{
	return nullptr;
}
