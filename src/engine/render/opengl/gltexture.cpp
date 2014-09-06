#include "gltexture.h"

#include "glextensions.h"

GLTexture::GLTexture() :
	_textureType(GL_TEXTURE_2D)
{
	glGenTextures(1, &_texture);
}

GLTexture::~GLTexture()
{
	glDeleteTextures(1, &_texture);
}

void GLTexture::load()
{
	//Set type
	switch (type())
	{
	case Texture1D:
		_textureType = GL_TEXTURE_1D;
		break;
	case Texture2D:
		_textureType = GL_TEXTURE_2D;
		break;
	case Texture3D:
		_textureType = GL_TEXTURE_3D;
		break;
	case CubeMap:
		_textureType = GL_TEXTURE_CUBE_MAP;
		break;
	default:
		break;
	}

	//Bind texture type
	glBindTexture(_textureType, _texture);

	//Set filter
	GLint glFilterMin = GL_NEAREST;
	GLint glFilterMag = GL_NEAREST;

	switch (filter())
	{
	case Point:
		glFilterMin = GL_NEAREST;
		glFilterMag = GL_NEAREST;
		break;
	case Bilinear:
		glFilterMin = GL_LINEAR;
		glFilterMag = GL_LINEAR;
		break;
	case Trilinear:
		glFilterMin = GL_LINEAR_MIPMAP_LINEAR;
		glFilterMag = GL_LINEAR;
		break;
	default:
		break;
	}

	glTexParameteri(_textureType, GL_TEXTURE_MIN_FILTER, glFilterMin);
	glTexParameteri(_textureType, GL_TEXTURE_MAG_FILTER, glFilterMag);

	//Set wrap mode to repeat
	GLint glWrapMode = GL_CLAMP;

	switch (wrap())
	{
	case Clamp:
		glWrapMode = GL_CLAMP;
		break;
	case Repeat:
		glWrapMode = GL_REPEAT;
		break;
	default:
		break;
	}

	glTexParameteri(_textureType, GL_TEXTURE_WRAP_S, glWrapMode);
	glTexParameteri(_textureType, GL_TEXTURE_WRAP_T, glWrapMode);
	glTexParameteri(_textureType, GL_TEXTURE_WRAP_R, glWrapMode);

	//Set anisotropic filtering
	glTexParameterf(_textureType, GL_TEXTURE_MAX_ANISOTROPY_EXT, float(anisotropicLevel()));

	//Set mipmap levels
	glTexParameteri(_textureType, GL_TEXTURE_MIN_FILTER, glFilterMin);
	glTexParameteri(_textureType, GL_TEXTURE_MAG_FILTER, glFilterMag);

	//Set format
	GLint glInternalFormat = GL_RGBA;
	switch (format())
	{
	case RGB:
		glInternalFormat = GL_RGB;
		break;
	case RGBA:
		glInternalFormat = GL_RGBA;
		break;
	default:
		break;
	}

	//Load pixels
	if (type() == CubeMap)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, glInternalFormat, images[0]->width, images[0]->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, images[0]->data);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, glInternalFormat, images[1]->width, images[1]->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, images[1]->data);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, glInternalFormat, images[2]->width, images[2]->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, images[2]->data);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, glInternalFormat, images[3]->width, images[3]->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, images[3]->data);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, glInternalFormat, images[4]->width, images[4]->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, images[4]->data);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, glInternalFormat, images[5]->width, images[5]->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, images[5]->data);
	}
	else
	{
		Image *image = images[0];
		glTexImage2D(_textureType, 0, 
			glInternalFormat,
			image->width,
			image->height,
			0, GL_RGBA, 
			GL_UNSIGNED_BYTE,
			image->data);
	}

	//Generate mipmaps
	glGenerateMipmap(_textureType);

	glBindTexture(_textureType, 0);
}

void GLTexture::unload()
{

}

void GLTexture::bind()
{
	glActiveTexture(_unit);
	glBindTexture(_textureType, _texture);
}

void GLTexture::unbind()
{
	glBindTexture(_textureType, 0);
}
