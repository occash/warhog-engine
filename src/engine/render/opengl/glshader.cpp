#include "glshader.h"

#include "glextensions.h"
#include <iostream>

class ShaderCompiler
{
public:
	ShaderCompiler(GLenum type) :
		shader(glCreateShader(type))
	{}

	~ShaderCompiler()
	{
		glDeleteShader(shader);
	}

	bool compile(const std::string& src)
	{
		//Load source
		const char *source[] = { src.c_str() };
		glShaderSource(shader, 1, source, NULL);

		//compile from source
		glCompileShader(shader);

		//Check compilation status
		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status != GL_TRUE)
		{
			char buffer[512];
			glGetShaderInfoLog(shader, 512, NULL, buffer);
			std::cout << buffer << std::endl;

			return false;
		}

		return true;
	}

	GLuint shader;

};

GLShader::GLShader() :
	_program(glCreateProgram())
{
}

GLShader::~GLShader()
{
	glDeleteProgram(_program);
}

void GLShader::bind()
{
	glUseProgram(_program);
}

void GLShader::unbind()
{
	glUseProgram(0);
}

void GLShader::load()
{
	ShaderCompiler vertexCompiler(GL_VERTEX_SHADER);
	vertexCompiler.compile(vertexSource);

	ShaderCompiler pixelCompiler(GL_FRAGMENT_SHADER);
	pixelCompiler.compile(pixelSource);

	glAttachShader(_program, vertexCompiler.shader);
	glAttachShader(_program, pixelCompiler.shader);
}

void GLShader::unload()
{

}

ShaderVariable *GLShader::variable(const char *) const
{

}

ShaderBlock *GLShader::block(const char *) const
{

}
