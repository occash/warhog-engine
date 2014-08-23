#ifndef MATERIAL_H
#define MATERIAL_H

#include "global.h"
#include "meta/any.h"

#include <string>

class ENGINE_EXPORT Material
{
public:
	const char *shader() const;
	void setShader(const char *name);

	virtual void bind();
	virtual void unbind();
	//virtual int propertyCount() const;
	//virtual const char *propertyName() const;
	virtual Any property(const char *name) const;
	virtual void setProperty(const char *name, const Any& value);

protected:
	virtual void createProgram(const char *name);

private:
	std::string _shader;

};

#endif
