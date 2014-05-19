#ifndef SHADER_H
#define SHADER_H

#include <glm/glm.hpp>
#include <string>

class Program;

class Shader
{
public:
    Shader(const std::string& source, glm::uint type);
    virtual ~Shader();

    bool compile();

private:
    friend class Program;

    std::string _source;
    glm::uint _type;
    glm::uint _shader;
};

#endif