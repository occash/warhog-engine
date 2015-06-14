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
    virtual ShaderVariable *variable(const char *name) const;

    virtual void get(void *, int);
    virtual void set(void *, int);

	template<typename T>
	void set(const T& t)
	{
		set((void *)&t, sizeof(T));
	}

	template<typename T, unsigned int N>
	void set(const T (&t)[N])
	{
		set((void *)t, sizeof(T) * N);
	}
};

class Shader
{
public:
    virtual void bind();
    virtual void unbind();

    virtual void load();
    virtual void unload();
	virtual unsigned int getProgram() { return 0; }

    virtual ShaderVariable *variable(const char *) const;
    virtual ShaderBlock *block(const char *) const;

    std::string vertexSource;
    std::string pixelSource;
};

#endif