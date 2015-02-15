#ifndef GLSHADER_H
#define GLSHADER_H

#include "../../shader.h"
#include <vector>
#include <map>

class GLShader;
class GLShaderBlock;

class GLShaderVariable : public ShaderVariable
{
public:
    GLShaderVariable(GLShaderVariable&& other);
    ~GLShaderVariable();

    const char *name() const override;
    Type type() const override;

    Any get() const override;
    void set(const Any&) override;

private:
    friend class GLShader;
    GLShaderVariable(GLShader *shader, unsigned int program, unsigned int buffer, int location);

    TypeTable *_init(unsigned int program, int location);

private:
    GLShader *_shader;
    const char *_name;
    Type _type;
    unsigned int _buffer;
    int _offset;
    int _size;

};

class GLGlobalVariable : public ShaderVariable
{
public:
    GLGlobalVariable(GLGlobalVariable&& other);
    ~GLGlobalVariable();

    const char *name() const override;
    Type type() const override;

    Any get() const override;
    void set(const Any&) override;

private:
    friend class GLShader;
    GLGlobalVariable(GLShader *shader, unsigned int program, int location);

    TypeTable *_init(unsigned int program, int location);

private:
    GLShader *_shader;
    const char *_name;
    Type _type;
    unsigned int _internalType;
    unsigned int _index;

};

class GLShaderBlock : public ShaderBlock
{
public:
    GLShaderBlock(GLShaderBlock&& other);
    ~GLShaderBlock();

    const char *name() const override;
    ShaderVariable *variable(const char *name) const override;

    void get(void *, int) override;
    void set(void *, int) override;

private:
    friend class GLShader;
    GLShaderBlock(GLShader *shader, const char *name, unsigned int program, int location);

private:
    friend class GLShader;
    static unsigned int _globalBind;

    GLShader *_shader;
    const char *_name;
    unsigned int _buffer;
    int _size;

};

class GLShader : public Shader
{
public:
    GLShader();
    ~GLShader();

    void bind() override;
    void unbind() override;

    void load() override;
    void unload() override;

    ShaderVariable *variable(const char *name) const override;
    ShaderBlock *block(const char *name) const override;

    unsigned int acquireTexture(ShaderVariable *);

private:
    unsigned int _program;
    std::vector<GLShaderBlock> _blocks;
    std::map<std::string, int> _blockNames;
    std::vector<GLShaderVariable> _variables;
    std::map<std::string, int> _variableNames;
    std::vector<GLGlobalVariable> _globals;
    std::map<std::string, int> _globalNames;
    std::map<ShaderVariable *, unsigned int> _textureUnits;
    unsigned int _unitCounter;

};

#endif