#include "gbuffer.h"

#include <iostream>

GBuffer::GBuffer(int width, int height)
{
    glGenFramebuffers(1, &_fbo);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _fbo);

    glGenTextures(MaxNumber, _textures);
    glGenTextures(1, &_depth);

    //Color attachment
    for (unsigned int i = 0; i < MaxNumber; i++) {
        glBindTexture(GL_TEXTURE_2D, _textures[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 
            0, GL_RGB, GL_FLOAT, nullptr);
        glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, 
            GL_TEXTURE_2D, _textures[i], 0);
    }

    //Depth attachment
    glBindTexture(GL_TEXTURE_2D, _depth);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height, 
        0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, 
        GL_TEXTURE_2D, _depth, 0);

    GLenum drawBuffers[] = { 
        GL_COLOR_ATTACHMENT0, 
        GL_COLOR_ATTACHMENT1, 
        GL_COLOR_ATTACHMENT2, 
        GL_COLOR_ATTACHMENT3 
    };
    glDrawBuffers(MaxNumber, drawBuffers);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "Frame buffer not created" << std::endl;
    }

    // restore default FBO
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}


GBuffer::~GBuffer()
{
    glDeleteFramebuffers(1, &_fbo);
}

void GBuffer::bind(Operation op)
{
    glBindFramebuffer((GLuint)op, _fbo);
}
