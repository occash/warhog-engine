#ifndef TEXTURE_H
#define TEXTURE_H

#include "global.h"
#include "meta/object.h"

#include <array>

struct Image
{
	unsigned char *data;
	unsigned char **rowPtrs;
	unsigned int width;
	unsigned int height;
	unsigned int bitDepth;
	unsigned int channels;
	unsigned int colorType;
};

class ENGINE_EXPORT Texture : public Object
{
	U_OBJECT(Texture, Object)
public:
    enum Type 
	{
        Texture1D,
        Texture2D,
        Texture3D,
        CubeMap
    };

    enum Filter 
	{
        Point, 
        Bilinear,
        Trilinear
    };

    enum Wrap 
	{
        Repeat,
        Clamp
    };

	enum Format 
	{
		RGB,
		RGBA
	};

	Texture();
	~Texture();

    Type type() const;
	void setType(Type type);

	Filter filter() const;
	void setFilter(Filter filter);

	Wrap wrap() const;
	void setWrap(Wrap wrap);

	Format format() const;
	void setFormat(Format format);

	int anisotropicLevel() const;
	void setAnisotropicLevel(int level);

	int mipmapCount() const;
	void setMipmapCount(int count);

	virtual void load();
	virtual void unload();

	virtual void bind();
	virtual void unbind();

public:
	std::array<Image *, 6> images;

private:
    Type _type;
    Filter _filter;
    Wrap _wrap;
	Format _format;
	int _anisoLevel;
    int _mipmaps;

};

#endif