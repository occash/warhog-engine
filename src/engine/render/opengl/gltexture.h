#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include "../../texture.h"

class GLTexture : public Texture
{
public:
	GLTexture();
	~GLTexture();

	void load() override;
	void unload() override;

	void bind() override;
	void unbind() override;

private:
	//friend class FrameBuffer;
	unsigned int _textureType;
	unsigned int _texture;
	unsigned int _unit;
};

#endif