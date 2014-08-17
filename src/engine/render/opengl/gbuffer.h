#pragma once

#include <GL/glew.h>

class GBuffer
{
public:
    enum TextureType
    {
        Position,
        Diffuse,
        Normal,
        Texcoord,
        MaxNumber
    };

    enum Operation
    {
        Read = GL_READ_FRAMEBUFFER,
        Write = GL_DRAW_FRAMEBUFFER
    };

    GBuffer(int width, int height);
    ~GBuffer();

    void bind(Operation op);

private:
    GLuint _fbo;
    GLuint _textures[MaxNumber];
    GLuint _depth;
};

