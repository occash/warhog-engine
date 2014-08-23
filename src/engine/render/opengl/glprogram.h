#ifndef PROGRAM_H
#define PROGRAM_H

#include <glm/glm.hpp>
#include "uniform.h"
#include "uniformblock.h"

class GLShader;
class Mesh;

class GLProgram
{
public:
    GLProgram();
    virtual ~GLProgram();

    bool valid();

    void attach(const GLShader&);
    void detach(const GLShader&);
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