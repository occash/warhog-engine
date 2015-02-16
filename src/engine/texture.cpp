#include "texture.h"

Texture::Texture() :
    _type(Texture2D),
    _filter(Point),
    _wrap(Clamp),
    _format(RGBA),
    _anisoLevel(1),
    _mipmaps(0)
{
}

Texture::~Texture()
{
}

void Texture::load()
{
}

void Texture::unload()
{
}

void Texture::bind()
{
}

void Texture::unbind()
{
}

Texture::Type Texture::type() const
{
    return _type;
}

void Texture::setType(Type type)
{
    _type = type;
}

Texture::Filter Texture::filter() const
{
    return _filter;
}

void Texture::setFilter(Filter filter)
{
    _filter = filter;
}

Texture::Wrap Texture::wrap() const
{
    return _wrap;
}

void Texture::setWrap(Wrap wrap)
{
    _wrap = wrap;
}

Texture::Format Texture::format() const
{
    return _format;
}

void Texture::setFormat(Format format)
{
    _format = format;
}

int Texture::anisotropicLevel() const
{
    return _anisoLevel;
}

void Texture::setAnisotropicLevel(int level)
{
    _anisoLevel = level;
}

int Texture::mipmapCount() const
{
    return _mipmaps;
}

void Texture::setMipmapCount(int count)
{
    _mipmaps = count;
}
