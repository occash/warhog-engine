#ifndef MATERIAL_H
#define MATERIAL_H

#include "../global.h"

#include <string>
#include <entityx/Entity.h>

using namespace entityx;
class Program;

class ENGINE_EXPORT MaterialComponent : public Component<MaterialComponent>
{
public:
    MaterialComponent();
    virtual ~MaterialComponent();

	Program *program() const { return _program;  }

	std::string shader() const;
	void setShader(const std::string& name);

private:
	std::string _name;
    Program *_program;

};

#endif
