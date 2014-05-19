#include "shader.h"

#include <GL/glew.h>
#include <iostream>

Shader::Shader(const std::string& source, GLenum type)
    : _source(source),
    _type(type),
    _shader(glCreateShader(type))
{
}


Shader::~Shader()
{
    glDeleteShader(_shader);
}

bool Shader::compile()
{
    //Load source
    const char *source[] = { _source.c_str() };
    glShaderSource(_shader, 1, source, NULL);

    //compile from source
    glCompileShader(_shader);

    //Check compilation status
    GLint status;
    glGetShaderiv(_shader, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE)
    {
        char buffer[512];
        glGetShaderInfoLog(_shader, 512, NULL, buffer); 
        std::cout << buffer << std::endl;

        return false;
    }

    return true;
}
