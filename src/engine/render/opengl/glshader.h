#ifndef GLSHADER_H
#define GLSHADER_H

#include "../../shader.h"

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

};

#endif