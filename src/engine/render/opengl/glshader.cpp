#include "glshader.h"
#include "glextensions.h"
#include "gltexture.h"

#include "../../meta/any.h"

#include <iostream>
#include <glm/glm.hpp>

static TypeTable *dispatchType(int glType);

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
	_program(glCreateProgram()),
	_unitCounter(0)
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
		//Query name length and number of fields
		const GLenum blockParams[] = { GL_NAME_LENGTH, GL_NUM_ACTIVE_VARIABLES };
		GLint paramValues[2];
		glGetProgramResourceiv(_program, GL_UNIFORM_BLOCK, i, 2, blockParams, 2, 0, paramValues);
		char *blockName = new char[paramValues[0] + 1];
		glGetProgramResourceName(_program, GL_UNIFORM_BLOCK, i, paramValues[0] + 1, 0, const_cast<char*>(blockName));

		_blocks.push_back(GLShaderBlock(this, blockName, _program, i));
		_blockNames.insert(std::make_pair((_blocks.data() + i)->name(), i));		

		//Create variables
		_variables.reserve(paramValues[1]);
		std::vector<GLint> vars(paramValues[1]);
		GLenum activeVars = GL_ACTIVE_VARIABLES;
		glGetProgramResourceiv(_program, GL_UNIFORM_BLOCK, i, 1, &activeVars, blockParams[1], 0, vars.data());
		for (int n = 0; n < paramValues[1]; ++n)
		{
			_variables.push_back(GLShaderVariable(this, _program, (_blocks.data() + i)->_buffer, vars[n]));
			_variableNames.insert(std::make_pair((_variables.data() + _variables.size() - 1)->name(), _variables.size() - 1));
		}
	}

	//Get the number of global variables
	glGetProgramInterfaceiv(_program, GL_UNIFORM, GL_ACTIVE_RESOURCES, &numBlocks);
	_globals.reserve(numBlocks);

	for (int i = 0; i < numBlocks; ++i)
	{
		//Query location
		const GLenum globalParams[] = { GL_LOCATION };
		GLint location;
		glGetProgramResourceiv(_program, GL_UNIFORM, i, 1, globalParams, 1, 0, &location);
		if (location == -1) continue; //Skip block uniforms

		_globals.push_back(GLGlobalVariable(this, _program, location));
		_globalNames.insert(std::make_pair((_globals.data() + _globals.size() - 1)->name(), _globals.size() - 1));
	}
}

void GLShader::unload()
{

}

ShaderVariable *GLShader::variable(const char *name) const
{
	auto varId = _variableNames.find(name);
	if (varId == _variableNames.end())
	{
		auto globId = _globalNames.find(name);
		if (globId == _globalNames.end())
			return nullptr;

		const GLGlobalVariable *data = _globals.data() + globId->second;
		return const_cast<GLGlobalVariable *>(data);
	}

	const GLShaderVariable *data = _variables.data() + varId->second;
	return const_cast<GLShaderVariable *>(data);
}

ShaderBlock *GLShader::block(const char *name) const
{
	auto blockId = _blockNames.find(name);
	if (blockId == _blockNames.end())
		return nullptr;

	const GLShaderBlock *data = _blocks.data() + blockId->second;
	return const_cast<GLShaderBlock *>(data);
}

unsigned int GLShader::acquireTexture(ShaderVariable *variable)
{
	auto textureUnit = _textureUnits.find(variable);
	if (textureUnit == _textureUnits.end()) //New unit
	{
		auto ret = _textureUnits.insert(std::make_pair(variable, _unitCounter++));
		if (ret.second)
			textureUnit = ret.first;
	}

	return textureUnit->second;
}

GLShaderBlock::GLShaderBlock(GLShader *shader, const char* name, unsigned int program, int location) :
	_shader(shader),
	_name(name),
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

	std::vector<char> nulls(_size, '\0');
	set(nulls.data(), _size);
}

GLShaderBlock::GLShaderBlock(GLShaderBlock &&other) :
	_shader(other._shader),
	_name(other._name),
	_buffer(other._buffer),
	_size(other._size)
{
	other._name = nullptr;
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

const char *GLShaderBlock::name() const
{
	return _name;
}

ShaderVariable *GLShaderBlock::variable(const char *name) const
{
	std::string fullName = this->name();
	fullName.append(".");
	fullName.append(name);

	return _shader->variable(fullName.c_str());
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

GLShaderVariable::GLShaderVariable(GLShader *shader, unsigned int program, unsigned int buffer, int location) :
	_shader(shader),
	_type(_init(program, location)),
	_buffer(buffer)
{
}

GLShaderVariable::GLShaderVariable(GLShaderVariable &&other) :
	_shader(other._shader),
	_name(other._name),
	_type(other._type),
	_buffer(other._buffer),
	_offset(other._offset),
	_size(other._size)
{
}

GLShaderVariable::~GLShaderVariable()
{
}

const char *GLShaderVariable::name() const
{
	return _name;
}

Type GLShaderVariable::type() const
{
	return _type;
}

Any GLShaderVariable::get() const
{
	return Any();
}

void GLShaderVariable::set(const Any& value)
{
	if (_type != value.type())
		return;

	void *data = value.data();
	bool smallType = _type.size() <= sizeof(void *);

	//Bind texture unit
	if (_type == Type::from<Texture*>())
	{
		Texture *texture = any_cast<Texture *>(value);
		unsigned int unit = _shader->acquireTexture(this);
		glActiveTexture(GL_TEXTURE0 + unit);
		texture->bind();
		void *data = (void *)unit;
	}

	glBindBuffer(GL_UNIFORM_BUFFER, _buffer);
	glBufferSubData(GL_UNIFORM_BUFFER, _offset, _size, smallType ? &data : data);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

TypeTable *GLShaderVariable::_init(unsigned int program, int location)
{
	//Query variable params
	const GLenum varParams[] = { GL_NAME_LENGTH, GL_TYPE, GL_OFFSET };
	GLint varValues[3];
	glGetProgramResourceiv(program, GL_UNIFORM, location, 3, varParams, 3, 0, varValues);

	_offset = varValues[2];

	//Query name
	_name = new char[varValues[0] + 1];
	glGetProgramResourceName(program, GL_UNIFORM, location, varValues[0] + 1, 0, const_cast<char*>(_name));

	TypeTable *table = dispatchType(varValues[1]);
	_size = table->get_size();

	return table;
}

static TypeTable *dispatchType(int glType)
{
	switch (glType)
	{
	case GL_FLOAT:
		return Table<float>::get();
	case GL_FLOAT_VEC2:
		return Table<glm::vec2>::get();
	case GL_FLOAT_VEC3:
		return Table<glm::vec3>::get();
	case GL_FLOAT_VEC4:
		return Table<glm::vec4>::get();
	case GL_DOUBLE:
		return Table<double>::get();
	case GL_DOUBLE_VEC2:
		return Table<glm::dvec2>::get();
	case GL_DOUBLE_VEC3:
		return Table<glm::dvec3>::get();
	case GL_DOUBLE_VEC4:
		return Table<glm::dvec4>::get();
	case GL_INT:
		return Table<int>::get();
	case GL_INT_VEC2:
		return Table<glm::ivec2>::get();
	case GL_INT_VEC3:
		return Table<glm::ivec3>::get();
	case GL_INT_VEC4:
		return Table<glm::ivec4>::get();
	case GL_UNSIGNED_INT:
		return Table<unsigned int>::get();
	case GL_UNSIGNED_INT_VEC2:
		return Table<glm::uvec2>::get();
	case GL_UNSIGNED_INT_VEC3:
		return Table<glm::uvec3>::get();
	case GL_UNSIGNED_INT_VEC4:
		return Table<glm::uvec4>::get();
	case GL_BOOL:
		return Table<bool>::get();
	case GL_BOOL_VEC2:
		return Table<glm::bvec2>::get();
	case GL_BOOL_VEC3:
		return Table<glm::bvec3>::get();
	case GL_BOOL_VEC4:
		return Table<glm::bvec4>::get();
	case GL_FLOAT_MAT2:
		return Table<glm::mat2>::get();
	case GL_FLOAT_MAT3:
		return Table<glm::mat3>::get();
	case GL_FLOAT_MAT4:
		return Table<glm::mat4>::get();
	case GL_FLOAT_MAT2x3:
		return Table<glm::mat2x3>::get();
	case GL_FLOAT_MAT2x4:
		return Table<glm::mat2x4>::get();
	case GL_FLOAT_MAT3x2:
		return Table<glm::mat3x2>::get();
	case GL_FLOAT_MAT3x4:
		return Table<glm::mat3x4>::get();
	case GL_FLOAT_MAT4x2:
		return Table<glm::mat4x2>::get();
	case GL_FLOAT_MAT4x3:
		return Table<glm::mat4x3>::get();
	case GL_DOUBLE_MAT2:
		return Table<glm::dmat2>::get();
	case GL_DOUBLE_MAT3:
		return Table<glm::dmat3>::get();
	case GL_DOUBLE_MAT4:
		return Table<glm::dmat4>::get();
	case GL_DOUBLE_MAT2x3:
		return Table<glm::dmat2x3>::get();
	case GL_DOUBLE_MAT2x4:
		return Table<glm::dmat2x4>::get();
	case GL_DOUBLE_MAT3x2:
		return Table<glm::dmat3x2>::get();
	case GL_DOUBLE_MAT3x4:
		return Table<glm::dmat3x4>::get();
	case GL_DOUBLE_MAT4x2:
		return Table<glm::dmat4x2>::get();
	case GL_DOUBLE_MAT4x3:
		return Table<glm::dmat4x3>::get();
	case GL_SAMPLER_1D:
		return Table<Texture *>::get();
	case GL_SAMPLER_2D:
		return Table<Texture *>::get();
	case GL_SAMPLER_3D:
		return Table<Texture *>::get();
	case GL_SAMPLER_CUBE:
		return Table<Texture *>::get();
	/*case GL_SAMPLER_1D_SHADOW:
		return Table<sampler1DShadow>::get();
	case GL_SAMPLER_2D_SHADOW:
		return Table<sampler2DShadow>::get();
	case GL_SAMPLER_1D_ARRAY:
		return Table<sampler1DArray>::get();
	case GL_SAMPLER_2D_ARRAY:
		return Table<sampler2DArray>::get();
	case GL_SAMPLER_1D_ARRAY_SHADOW:
		return Table<sampler1DArrayShadow>::get();
	case GL_SAMPLER_2D_ARRAY_SHADOW:
		return Table<sampler2DArrayShadow>::get();
	case GL_SAMPLER_2D_MULTISAMPLE:
		return Table<sampler2DMS>::get();
	case GL_SAMPLER_2D_MULTISAMPLE_ARRAY:
		return Table<sampler2DMSArray>::get();
	case GL_SAMPLER_CUBE_SHADOW:
		return Table<samplerCubeShadow>::get();
	case GL_SAMPLER_BUFFER:
		return Table<samplerBuffer>::get();
	case GL_SAMPLER_2D_RECT:
		return Table<sampler2DRect>::get();
	case GL_SAMPLER_2D_RECT_SHADOW:
		return Table<sampler2DRectShadow>::get();
	case GL_INT_SAMPLER_1D:
		return Table<isampler1D>::get();
	case GL_INT_SAMPLER_2D:
		return Table<isampler2D>::get();
	case GL_INT_SAMPLER_3D:
		return Table<isampler3D>::get();
	case GL_INT_SAMPLER_CUBE:
		return Table<isamplerCube>::get();
	case GL_INT_SAMPLER_1D_ARRAY:
		return Table<isampler1DArray>::get();
	case GL_INT_SAMPLER_2D_ARRAY:
		return Table<isampler2DArray>::get();
	case GL_INT_SAMPLER_2D_MULTISAMPLE:
		return Table<isampler2DMS>::get();
	case GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY:
		return Table<isampler2DMSArray>::get();
	case GL_INT_SAMPLER_BUFFER:
		return Table<isamplerBuffer>::get();
	case GL_INT_SAMPLER_2D_RECT:
		return Table<isampler2DRect>::get();
	case GL_UNSIGNED_INT_SAMPLER_1D:
		return Table<usampler1D>::get();
	case GL_UNSIGNED_INT_SAMPLER_2D:
		return Table<usampler2D>::get();
	case GL_UNSIGNED_INT_SAMPLER_3D:
		return Table<usampler3D>::get();
	case GL_UNSIGNED_INT_SAMPLER_CUBE:
		return Table<usamplerCube>::get();
	case GL_UNSIGNED_INT_SAMPLER_1D_ARRAY:
		return Table<usampler2DArray>::get();
	case GL_UNSIGNED_INT_SAMPLER_2D_ARRAY:
		return Table<usampler2DArray>::get();
	case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE:
		return Table<usampler2DMS>::get();
	case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY:
		return Table<usampler2DMSArray>::get();
	case GL_UNSIGNED_INT_SAMPLER_BUFFER:
		return Table<usamplerBuffer>::get();
	case GL_UNSIGNED_INT_SAMPLER_2D_RECT:
		return Table<usampler2DRect>::get();*/
	}

	return nullptr;
}

GLGlobalVariable::GLGlobalVariable(GLShader *shader, unsigned int program, int location) :
	_shader(shader),
	_type(_init(program, location)),
	_index(location)
{
}

GLGlobalVariable::GLGlobalVariable(GLGlobalVariable &&other) :
	_shader(other._shader),
	_name(other._name),
	_type(other._type),
	_internalType(other._internalType),
	_index(other._index)
{
}

GLGlobalVariable::~GLGlobalVariable()
{
}

const char *GLGlobalVariable::name() const
{
	return _name;
}

Type GLGlobalVariable::type() const
{
	return _type;
}

Any GLGlobalVariable::get() const
{
	return Any();
}

void GLGlobalVariable::set(const Any& value)
{
	if (_type != value.type())
		return;

	switch (_internalType)
	{
	case GL_SAMPLER_1D:
	case GL_SAMPLER_2D:
	case GL_SAMPLER_3D:
	case GL_SAMPLER_CUBE:
	{
		Texture *texture = any_cast<Texture *>(value);
		unsigned int unit = _shader->acquireTexture(this);
		glActiveTexture(GL_TEXTURE0 + unit);
		texture->bind();
		glUniform1i(_index, unit);
	}
		break;
	default:
		break;
	}
}

TypeTable *GLGlobalVariable::_init(unsigned int program, int location)
{
	//Query variable params
	const GLenum varParams[] = { GL_NAME_LENGTH, GL_TYPE };
	GLint varValues[2];
	glGetProgramResourceiv(program, GL_UNIFORM, location, 2, varParams, 2, 0, varValues);

	//Query name
	_name = new char[varValues[0]];
	glGetProgramResourceName(program, GL_UNIFORM, location, varValues[0], 0, const_cast<char*>(_name));

	_internalType = varValues[1];
	TypeTable *table = dispatchType(varValues[1]);
	return table;
}
