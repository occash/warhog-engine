#include "image.h"

#include <fstream>
#include <iostream>

#define PNGSIGSIZE 8

Image::Image(const std::string& name)
    : _data(nullptr),
    _rowPtrs(nullptr),
    _width(0),
    _height(0),
    _bitDepth(0),
    _channels(0),
    _colorType(0)
{
    /*std::ifstream source;
    source.open(name, std::ios::in | std::ios::binary);

    //Validate png type and read
    if (!source.is_open() || !validate(source))
        std::cout << "Source is not valid png image format";
    else
        readData(source);*/
}

Image::~Image()
{
    delete[] _rowPtrs;
    delete[] _data;
}

/*bool Image::validate(std::istream& source)
{
    png_byte pngsig[PNGSIGSIZE];
    int is_png = 0;

    //Read png header
    source.read((char *)pngsig, PNGSIGSIZE);

    //Check if header actually read
    if (source.bad())
        return false;

    //Check if header is png header
    is_png = png_sig_cmp(pngsig, 0, PNGSIGSIZE);
    return (is_png == 0);
}

void Image::readData(std::istream& source)
{
    //Create read structure
    png_structp pngPtr = png_create_read_struct(
        PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!pngPtr)
    {
        std::cout << "Cannot initialize read struct";
        return;
    }

    //Create info structure
    png_infop infoPtr = png_create_info_struct(pngPtr);
    if (!infoPtr)
    {
        std::cout << "Cannot create info struct";
        png_destroy_read_struct(&pngPtr, (png_infopp)0, (png_infopp)0);
        return;
    }
    
    //Set error handler
    //If error occurred it will jump to code in if body
    if (setjmp(png_jmpbuf(pngPtr)))
    {
        png_destroy_read_struct(&pngPtr, &infoPtr, (png_infopp)0);
        if (_rowPtrs != nullptr)
        {
            delete[] _rowPtrs;
            _rowPtrs = nullptr;
        }    
        if (_data != nullptr)
        {
            delete[] _data;
            _data = nullptr;
        }
        return;
    }

    //Set custom read function (read from std::stream)
    png_set_read_fn(pngPtr, (png_voidp)&source, Image::pngReadData);

    //Let libpng know that we already read 8 bytes
    png_set_sig_bytes(pngPtr, PNGSIGSIZE);
    png_read_info(pngPtr, infoPtr);

    //Get basic info
    _width = png_get_image_width(pngPtr, infoPtr);
    _height = png_get_image_height(pngPtr, infoPtr);
    _bitDepth = png_get_bit_depth(pngPtr, infoPtr);
    _channels = png_get_channels(pngPtr, infoPtr);
    _colorType = png_get_color_type(pngPtr, infoPtr);

    //Handle different color type, depth and channels
    //and convert if possible
    switch (_colorType) {
    case PNG_COLOR_TYPE_PALETTE:
        png_set_palette_to_rgb(pngPtr);
        _channels = 3;
        break;
    case PNG_COLOR_TYPE_GRAY:
        if (_bitDepth < 8)
            png_set_expand_gray_1_2_4_to_8(pngPtr);
        _bitDepth = 8;
        break;
    }

    if (png_get_valid(pngPtr, infoPtr, PNG_INFO_tRNS)) {
        png_set_tRNS_to_alpha(pngPtr);
        _channels += 1;
    }

    if (_bitDepth == 16)
        png_set_strip_16(pngPtr);

    //Allocate memory for data and raws
    _rowPtrs = new png_bytep[_height];
    _data = new png_byte[_width * _height * _bitDepth * _channels / 8];

    //Set pointer to beginning of each row
    const unsigned int stride = _width * _bitDepth * _channels / 8;
    for (size_t i = 0; i < _height; i++) {
        png_uint_32 q = i * stride;
        _rowPtrs[i] = (png_bytep)_data + q;
    }

    //Actually read data
    png_read_image(pngPtr, _rowPtrs);

    png_destroy_read_struct(&pngPtr, &infoPtr, (png_infopp)0);
}

void Image::pngReadData(png_structp pngPtr, png_bytep data, png_size_t length)
{
    png_voidp a = png_get_io_ptr(pngPtr);
    ((std::istream*)a)->read((char*)data, length);
}*/

int Image::width() const
{
    return _width;
}

int Image::height() const
{
    return _height;
}

int Image::depth() const
{
    return _bitDepth;
}

int Image::channels() const
{
    return _channels;
}

unsigned char *Image::data() const
{
    return _data;
}

unsigned char *Image::row(int num) const
{
    return _rowPtrs[num];
}
