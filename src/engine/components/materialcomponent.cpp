#include "materialcomponent.h"
#include "../shader.h"
#include "../program.h"

#include "../render/opengl/glextensions.h"
#include <fstream>

std::string readFile(const std::string& fileName)
{
    std::string source;
    std::ifstream file(fileName);
    if(file.is_open()) 
    {
        source = std::string((std::istreambuf_iterator<char>(file)), 
            std::istreambuf_iterator<char>());
        file.close();
    }

    return source;
}

MaterialComponent::MaterialComponent()
    : _program(new Program())
{
}


MaterialComponent::~MaterialComponent(void)
{
}

std::string MaterialComponent::shader() const
{
	return _name;
}

void MaterialComponent::setShader(const std::string& name)
{
	_name = name;

	std::string vertexSource = readFile(name + ".vert");
	Shader vertex(vertexSource, GL_VERTEX_SHADER);
	if (!vertex.compile())
		return;

	std::string fragmentSource = readFile(name + ".frag");
	Shader fragment(fragmentSource, GL_FRAGMENT_SHADER);
	if (!fragment.compile())
		return;

	_program->attach(vertex);
	_program->attach(fragment);

	_program->bindFragData(0, "outColor");
	_program->link();

	/*_program->enableAttribute(&data, "position", 2, 5 * sizeof(GLfloat), 0);
	_program->enableAttribute(&data, "color", 3, 5 * sizeof(GLfloat), (void *)(2 * sizeof(GLfloat)));*/
}