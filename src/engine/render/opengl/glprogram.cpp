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

	//glBindAttribLocation(_program, 0, "position");
	//glBindAttribLocation(_program, 0, "color");

    /*GLint active;
    glGetProgramiv(_program, GL_ACTIVE_ATTRIBUTES, &active);
    for (int i = 0; i < active; ++i)
    {
        char name[256];
        //GLsizei length;
        GLint size;
        GLenum type;
        glGetActiveAttrib(_program, i, 256, nullptr, &size, &type, name);
    }*/
    

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
