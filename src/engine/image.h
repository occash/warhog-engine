#ifndef PICTURE_H
#define PICTURE_H

//#include <png.h>
#include <istream>

class Texture;

class Image
{
public:
	Image(const std::string& name);
	virtual ~Image();

    int width() const;
    int height() const;
    int depth() const;
    int channels() const;

    unsigned char *data() const;
    unsigned char *row(int num) const;

private:
    /*bool validate(std::istream& stream);
    void readData(std::istream& steram);
    static void pngReadData(png_structp pngPtr, 
        png_bytep data,
        png_size_t length);*/

private:
	friend class Texture;

    unsigned char *_data;
    unsigned char **_rowPtrs;
    unsigned int _width;
    unsigned int _height;
    unsigned int _bitDepth;
    unsigned int _channels;
    unsigned int _colorType;
};

#endif