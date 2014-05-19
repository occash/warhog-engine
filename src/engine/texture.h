#ifndef TEXTURE_H
#define TEXTURE_H

#include "global.h"

#include <glm/glm.hpp>
#include "image.h"

class ENGINE_EXPORT Texture
{
public:
    enum Type {
        Texture1D,
        Texture2D,
        Texture3D,
        CubeMap
    };

    enum Filter {
        Point, 
        Bilinear,
        Trilinear
    };

    enum Wrap {
        Repeat,
        Clamp
    };

	Texture(/*Type type, glm::uint unit*/);
	virtual ~Texture();

    Type type() const;
	void load(const Image& image);
	void bind();

private:
    friend class FrameBuffer;

    glm::uint _texture;
    glm::uint _unit;

public:
    Type _type;
    Filter _filter;
    Wrap _wrap;
    bool _mipmaps;

    unsigned char *_data;
    unsigned char **_rowPtrs;
    unsigned int _width;
    unsigned int _height;
    unsigned int _bitDepth;
    unsigned int _channels;
    unsigned int _colorType;

};

#endif