#ifndef PROGRAM_H
#define PROGRAM_H

#include <glm/glm.hpp>
#include "render/opengl/uniform.h"
#include "render/opengl/uniformblock.h"

class Shader;
class Mesh;

class Program
{
public:
    Program();
    virtual ~Program();

    bool valid();

    void attach(const Shader&);
    void detach(const Shader&);
    bool link();
    void use();

    void bindFragData(glm::uint, const char *);
    void bindAttrib(glm::uint, const char *);

	Uniform uniform(const char *);
    UniformBlock block(const char *);

private:
    friend class UniformBlock;
    static glm::uint _globalBind;

private:
    glm::uint _program;

};

#endif