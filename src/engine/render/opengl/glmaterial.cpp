#include "glmaterial.h"
#include "glshader.h"
#include "glextensions.h"

#include <fstream>

std::string readFile(const std::string& fileName)
{
	std::string source;
	std::ifstream file(fileName);
	if (file.is_open())
	{
		source = std::string((std::istreambuf_iterator<char>(file)),
			std::istreambuf_iterator<char>());
		file.close();
	}

	return source;
}

void GLMaterial::createProgram(const char *prog)
{
	std::string name = prog;
	std::string vertexSource = readFile(name + ".vert");
	GLShader vertex(vertexSource, GL_VERTEX_SHADER);
	if (!vertex.compile())
		return;

	std::string fragmentSource = readFile(name + ".frag");
	GLShader fragment(fragmentSource, GL_FRAGMENT_SHADER);
	if (!fragment.compile())
		return;

	_program.attach(vertex);
	_program.attach(fragment);

	_program.bindFragData(0, "outColor");
	_program.link();
}

void GLMaterial::bind()
{
	_program.use();
}

void GLMaterial::unbind()
{
}

/*int GLMaterial::propertyCount() const
{

}

const char * GLMaterial::propertyName() const
{

}*/

Any GLMaterial::property(const char *name) const
{
	return Any();
}

void GLMaterial::setProperty(const char *name, const Any& value)
{
	_program.uniform(name);
}
