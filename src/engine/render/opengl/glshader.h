#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>
#include <string>

class GLProgram;

class GLShader
{
public:
    GLShader(const std::string& source, glm::uint type);
    virtual ~GLShader();

    bool compile();

private:
    friend class GLProgram;

    std::string _source;
    glm::uint _type;
    glm::uint _shader;
};

#endif