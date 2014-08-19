#include "texture.h"

#include "render/opengl/glextensions.h"

Texture::Texture(/*Texture::Type type, GLuint unit*/)
	: _type((Type)GL_TEXTURE_2D),
    _texture(0),
	_unit(15)
{
	glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);

	//Set wrap mode to repeat
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Generate mipmap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}


Texture::~Texture(void)
{
	glDeleteTextures(1, &_texture);
}

void Texture::load(const Image& image)
{
	glActiveTexture(_unit);
    glBindTexture(GL_TEXTURE_2D, _texture);

    if (image._data)
    {
        GLint format = GL_RGBA;
        /*if (image._colorType == PNG_COLOR_TYPE_RGB)
            format = GL_RGB;
        else if (image._colorType == PNG_COLOR_TYPE_RGB_ALPHA)
            format = GL_RGBA;*/

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
            image._width,
            image._height,
            0, format, GL_UNSIGNED_BYTE,
            image._data);
    }
        
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind()
{
	glActiveTexture(_unit);
    glBindTexture(GL_TEXTURE_2D, _texture);
}

Texture::Type Texture::type() const
{
    return _type;
}
