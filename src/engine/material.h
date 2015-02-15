#ifndef MATERIAL_H
#define MATERIAL_H

#include "global.h"
#include "meta/any.h"

#include <string>

class Shader;
class ShaderBlock;

//Instance of Shader
class ENGINE_EXPORT Material
{
public:
    Material();
    ~Material();

    Shader *shader() const;
    void setShader(Shader *shader);

    Any property(const char *name) const;
    void setProperty(const char *name, const Any& value);

private:
    Shader *_shader;
    ShaderBlock *_material;

};

#endif
