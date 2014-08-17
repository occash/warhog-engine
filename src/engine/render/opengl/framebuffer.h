/*#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <glm/glm.hpp>

class Texture;

class FrameBuffer
{
public:
    enum AttachmentType {
        Color = 0x8CE0, //Range to 0x8CEF
        Depth = 0x8D00,
        Stensil = 0x8D20
    };
    FrameBuffer();
    ~FrameBuffer();

    void bind();
    void unbind();
    void attachTexture(AttachmentType type, const Texture& texture);

private:
    glm::uint _fbo;

};

#endif*/
