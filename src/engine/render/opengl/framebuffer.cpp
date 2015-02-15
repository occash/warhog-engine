/*  #include "framebuffer.h"
    #include "texture.h"

    #include <GL/glew.h>

    FrameBuffer::FrameBuffer()
    : _fbo(0)
    {
    glGenFramebuffers(1, &_fbo);
    }


    FrameBuffer::~FrameBuffer()
    {
    glDeleteFramebuffers(1, &_fbo);
    }

    void FrameBuffer::bind()
    {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _fbo);
    }

    void FrameBuffer::unbind()
    {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    }

    void FrameBuffer::attachTexture(AttachmentType type, const Texture& texture)
    {
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, type, texture._type, texture._texture, 0);
    }
*/