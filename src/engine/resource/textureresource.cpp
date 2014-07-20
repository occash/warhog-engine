#include "textureresource.h"

#include <png.h>
#include <iostream>

#define PNGSIGSIZE 8

bool validate(std::istream& source)
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

void pngReadData(png_structp pngPtr, png_bytep data, png_size_t length)
{
    png_voidp a = png_get_io_ptr(pngPtr);
    ((std::istream*)a)->read((char*)data, length);
}

void readData(std::istream& source, Texture *texture)
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
        if (texture->_rowPtrs != nullptr)
        {
            delete[] texture->_rowPtrs;
            texture->_rowPtrs = nullptr;
        }
        if (texture->_data != nullptr)
        {
            delete[] texture->_data;
            texture->_data = nullptr;
        }
        return;
    }

    //Set custom read function (read from std::stream)
    png_set_read_fn(pngPtr, (png_voidp)&source, pngReadData);

    //Let libpng know that we already read 8 bytes
    png_set_sig_bytes(pngPtr, PNGSIGSIZE);
    png_read_info(pngPtr, infoPtr);

    //Get basic info
    texture->_width = png_get_image_width(pngPtr, infoPtr);
    texture->_height = png_get_image_height(pngPtr, infoPtr);
    texture->_bitDepth = png_get_bit_depth(pngPtr, infoPtr);
    texture->_channels = png_get_channels(pngPtr, infoPtr);
    texture->_colorType = png_get_color_type(pngPtr, infoPtr);

    //Handle different color type, depth and channels
    //and convert if possible
    switch (texture->_colorType) {
    case PNG_COLOR_TYPE_PALETTE:
        png_set_palette_to_rgb(pngPtr);
        texture->_channels = 3;
        break;
    case PNG_COLOR_TYPE_GRAY:
        if (texture->_bitDepth < 8)
            png_set_expand_gray_1_2_4_to_8(pngPtr);
        texture->_bitDepth = 8;
        break;
    }

    if (png_get_valid(pngPtr, infoPtr, PNG_INFO_tRNS)) {
        png_set_tRNS_to_alpha(pngPtr);
        texture->_channels += 1;
    }

    if (texture->_bitDepth == 16)
        png_set_strip_16(pngPtr);

    //Allocate memory for data and raws
    texture->_rowPtrs = new png_bytep[texture->_height];
    texture->_data = new png_byte[texture->_width * texture->_height 
        * texture->_bitDepth * texture->_channels / 8];

    //Set pointer to beginning of each row
    const unsigned int stride = texture->_width * texture->_bitDepth 
        * texture->_channels / 8;
    for (size_t i = 0; i < texture->_height; i++) {
        png_uint_32 q = i * stride;
        texture->_rowPtrs[i] = (png_bytep)texture->_data + q;
    }

    //Actually read data
    png_read_image(pngPtr, texture->_rowPtrs);

    png_destroy_read_struct(&pngPtr, &infoPtr, (png_infopp)0);
}

bool TextureResource::load(std::istream& in, Object *&resource) const
{
    if (!validate(in))
        return false;

    Texture *texture = new Texture();
    readData(in, texture);

    resource = texture;
    return true;
}

bool TextureResource::save(std::ostream& out, Object *resource) const
{
    return false;
}
