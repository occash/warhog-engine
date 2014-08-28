#ifndef SHADER_H
#define SHADER_H

#include "meta/type.h"
#include <string>

class ShaderVariable
{
public:
	virtual const char *name() const;
	virtual Type type() const;

	virtual Any get() const;
	virtual void set(const Any&);
};

class ShaderBlock
{
public:
	virtual const char *name() const;
	virtual ShaderVariable *variable() const;

	virtual void get(void *, int);
	virtual void set(void *, int);

};

class Shader
{
public:
	virtual void bind();
	virtual void unbind();

	virtual void load();
	virtual void unload();

	virtual ShaderVariable *variable(const char *) const;
	virtual ShaderBlock *block(const char *) const;

	std::string vertexSource;
	std::string pixelSource;
};

#endif