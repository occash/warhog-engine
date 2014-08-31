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

	//Link shader objects together
	glLinkProgram(_program);

	//Check link status
	GLint status;
	glGetProgramiv(_program, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		glGetProgramInfoLog(_program, 512, NULL, buffer);
		std::cout << buffer << std::endl;

		return;
	}

	//Get resources from linked shader
	//Get the number of blocks
	GLint numBlocks = 0;
	glGetProgramInterfaceiv(_program, GL_UNIFORM_BLOCK, GL_ACTIVE_RESOURCES, &numBlocks);
	_blocks.reserve(numBlocks);

	for (int i = 0; i < numBlocks; ++i)
	{
		_blocks.push_back(GLShaderBlock(_program, i));
		GLenum nameParam = GL_NAME_LENGTH;
		int nameLength = 0;
		glGetProgramResourceiv(_program, GL_UNIFORM_BLOCK, i, 1, &nameParam, 1, 0, &nameLength);
		char *blockName = new char[nameLength];
		glGetProgramResourceName(_program, GL_UNIFORM_BLOCK, i, 256, 0, blockName);
		_names.insert(std::make_pair(blockName, i));

		/*//Query name and number of struct fields
		const GLenum blockParams[] = { GL_NAME_LENGTH, GL_NUM_ACTIVE_VARIABLES };
		GLint paramValues[2];
		glGetProgramResourceiv(_program, GL_UNIFORM_BLOCK, i, 2, blockParams, 2, 0, paramValues);
		char blockName[256];
		glGetProgramResourceName(_program, GL_UNIFORM_BLOCK, i, 256, 0, blockName);

		const GLenum activeVars[] = { GL_ACTIVE_VARIABLES };
		GLint blockVars[32];
		glGetProgramResourceiv(_program, GL_UNIFORM_BLOCK, i, 1, activeVars, blockParams[1], 0, blockVars);

		for (int n = 0; n < paramValues[1]; ++n)
		{
			const GLenum varParams[] = { GL_NAME_LENGTH, GL_TYPE, GL_LOCATION };
			GLint varValues[3];
			//glGetProgramResourceiv(_program, GL_UNIFORM, n, )+
		}*/
	}
}

void GLShader::unload()
{

}

ShaderVariable *GLShader::variable(const char *) const
{
	return nullptr;
}

ShaderBlock *GLShader::block(const char *name) const
{
	auto blockId = _names.find(name);
	if (blockId == _names.end())
		return nullptr;

	const GLShaderBlock *data = _blocks.data() + blockId->second;
	return const_cast<GLShaderBlock *>(data);
}

GLShaderBlock::GLShaderBlock(unsigned int program, int location) :
	_buffer(0),
	_size(0)
{
	GLuint b = _globalBind++;
	//Create new binding
	glUniformBlockBinding(program, location, b);
	glGetActiveUniformBlockiv(program, location, GL_UNIFORM_BLOCK_DATA_SIZE, &_size);

	//Generate buffer for block
	glGenBuffers(1, &_buffer);
	glBindBufferBase(GL_UNIFORM_BUFFER, b, _buffer);
}

GLShaderBlock::GLShaderBlock(GLShaderBlock &&other) :
	_buffer(other._buffer),
	_size(other._size)
{
	other._buffer = 0;
	other._size = 0;
}

GLShaderBlock::~GLShaderBlock()
{
	if (_buffer)
	{
		glDeleteBuffers(1, &_buffer);
		_globalBind--;
	}
}

unsigned int GLShaderBlock::_globalBind = 0;

const char * GLShaderBlock::name() const
{
	return nullptr;
}

ShaderVariable * GLShaderBlock::variable(const char *name) const
{
	return nullptr;
}

void GLShaderBlock::get(void *data, int size)
{
	if (size != _size)
	{
		std::cout << "Block size not equal to data size";
		return;
	}

	glBindBuffer(GL_UNIFORM_BUFFER, _buffer);
	glGetBufferSubData(GL_UNIFORM_BUFFER, 0, size, data);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void GLShaderBlock::set(void *data, int size)
{
	if (size != _size)
	{
		std::cout << "Block size not equal to data size";
		return;
	}

	glBindBuffer(GL_UNIFORM_BUFFER, _buffer);
	glBufferData(GL_UNIFORM_BUFFER, size,
		data, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
