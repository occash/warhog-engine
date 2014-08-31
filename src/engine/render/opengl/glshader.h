#ifndef GLSHADER_H
#define GLSHADER_H

#include "../../shader.h"
#include <vector>
#include <map>

class GLShader;

/*class GLShaderVariable : public ShaderVariable
{
public:
	const char *name() const override;
	Type type() const override;

	Any get() const override;
	void set(const Any&) override;

private:
	friend class GLShader;
	GLShaderVariable(bool block, int location);

};*/

class GLShaderBlock : public ShaderBlock
{
public:
	GLShaderBlock(GLShaderBlock &&other);
	~GLShaderBlock();

	const char *name() const override;
	ShaderVariable *variable(const char *name) const override;

	void get(void *, int) override;
	void set(void *, int) override;

private:
	friend class GLShader;
	GLShaderBlock(unsigned int program, int location);

private:
	static unsigned int _globalBind;

	unsigned int _buffer;
	int _size;

};

class GLShader : public Shader
{
public:
    GLShader();
    ~GLShader();

	void bind() override;
	void unbind() override;

	void load() override;
	void unload() override;

	ShaderVariable *variable(const char *) const override;
	ShaderBlock *block(const char *) const override;

private:
	unsigned int _program;
	std::vector<GLShaderBlock> _blocks;
	std::map<std::string, int> _names;

};

#endif