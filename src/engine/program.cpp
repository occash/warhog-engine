#include "program.h"
#include "shader.h"
#include "mesh.h"

#include "render/opengl/glextensions.h"
#include <iostream>

Program::Program(void)
    : _program(glCreateProgram())
{
}

Program::~Program(void)
{
    glDeleteProgram(_program);
}

glm::uint Program::_globalBind = 0;

void Program::attach(const Shader& shader)
{
    glAttachShader(_program, shader._shader);
}

void Program::detach(const Shader& shader)
{
    glDetachShader(_program, shader._shader);
}

bool Program::link()
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

void Program::use()
{
    glUseProgram(_program);
}

void Program::bindFragData(GLuint location, const char *name)
{
    glBindFragDataLocation(_program, location, name);
}

void Program::bindAttrib(GLuint location, const char *name)
{
	glBindAttribLocation(_program, location, name);
}

Uniform Program::uniform(const char *name)
{
    GLint loc = glGetUniformLocation(_program, name);
    return Uniform(loc);
}

UniformBlock Program::block(const char *name)
{
    GLint loc = glGetUniformBlockIndex(_program, name);
    return UniformBlock(_program, loc);
}

bool Program::valid()
{
    return glIsProgram(_program) == GL_TRUE;
}
