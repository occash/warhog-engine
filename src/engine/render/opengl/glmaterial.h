#ifndef GLMATERIAL_H
#define GLMATERIAL_H

#include "../../material.h"
#include "glprogram.h"

class GLMaterial : public Material
{
public:
	void bind() override;
	void unbind() override;

	//int propertyCount() const override;
	//const char *propertyName() const override;
	Any property(const char *name) const override;
	void setProperty(const char *name, const Any& value) override;

protected:
	void createProgram(const char *name) override;

public:
	GLProgram _program;

};

#endif