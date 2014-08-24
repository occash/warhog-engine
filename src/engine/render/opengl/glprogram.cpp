#include "glprogram.h"
#include "GLShader.h"
#include "glextensions.h"

#include <iostream>

GLProgram::GLProgram(void)
    : _program(glCreateProgram())
{
}

GLProgram::~GLProgram(void)
{
    glDeleteProgram(_program);
}

glm::uint GLProgram::_globalBind = 0;

void GLProgram::attach(const GLShader& shader)
{
    glAttachShader(_program, shader._shader);
}

void GLProgram::detach(const GLShader& shader)
{
    glDetachShader(_program, shader._shader);
}

bool GLProgram::link()
{
	//Link shader objects together
    glLinkProgram(_program);

	//Check link status
	glm::int_t status;
	glGetProgramiv(_program, GL_LINK_STATUS, &status);
	if(status != GL_TRUE)
	{
		char buffer[512];
		glGetProgramInfoLog(_program, 512, NULL, buffer); 
		std::cout << buffer << std::endl;

		return false;
	}

	GLint numBlocks = 0;
	glGetProgramInterfaceiv(_program, GL_UNIFORM_BLOCK, GL_ACTIVE_RESOURCES, &numBlocks);
	for (int i = 0; i < numBlocks; ++i)
	{
		//Query name and number of struct fields
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
		}
	}

    return true;
}

void GLProgram::use()
{
    glUseProgram(_program);
}

void GLProgram::bindFragData(GLuint location, const char *name)
{
    glBindFragDataLocation(_program, location, name);
}

void GLProgram::bindAttrib(GLuint location, const char *name)
{
	glBindAttribLocation(_program, location, name);
}

Uniform GLProgram::uniform(const char *name)
{
    GLint loc = glGetUniformLocation(_program, name);
    return Uniform(loc);
}

UniformBlock GLProgram::block(const char *name)
{
    GLint loc = glGetUniformBlockIndex(_program, name);
    return UniformBlock(_program, loc);
}

bool GLProgram::valid()
{
    return glIsProgram(_program) == GL_TRUE;
}
