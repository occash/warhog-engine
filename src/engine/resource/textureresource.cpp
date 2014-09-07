#include "textureresource.h"
#include "../render/renderer.h"

#include <libpng/png.h>
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

void pngWriteData(png_structp png_ptr, png_bytep data, png_size_t length)
{
	png_voidp a = png_get_io_ptr(png_ptr);
	((std::ostream*)a)->write((char*)data, length);
}

void pngFlushData(png_structp)
{
}

void readData(std::istream& source, Image *image)
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
        if (image->rowPtrs != nullptr)
        {
            delete[] image->rowPtrs;
            image->rowPtrs = nullptr;
        }
        if (image->data != nullptr)
        {
            delete[] image->data;
            image->data = nullptr;
        }
        return;
    }

    //Set custom read function (read from std::stream)
    png_set_read_fn(pngPtr, (png_voidp)&source, pngReadData);

    //Let libpng know that we already read 8 bytes
    png_set_sig_bytes(pngPtr, PNGSIGSIZE);
    png_read_info(pngPtr, infoPtr);

    //Get basic info
    image->width = png_get_image_width(pngPtr, infoPtr);
    image->height = png_get_image_height(pngPtr, infoPtr);
    image->bitDepth = png_get_bit_depth(pngPtr, infoPtr);
    image->channels = png_get_channels(pngPtr, infoPtr);
    image->colorType = png_get_color_type(pngPtr, infoPtr);

    //Handle different color type, depth and channels
    //and convert if possible
    switch (image->colorType) 
	{
    case PNG_COLOR_TYPE_PALETTE:
        png_set_palette_to_rgb(pngPtr);
        image->channels = 3;
        break;
    case PNG_COLOR_TYPE_GRAY:
        if (image->bitDepth < 8)
            png_set_expand_gray_1_2_4_to_8(pngPtr);
        image->bitDepth = 8;
        break;
    }

    if (png_get_valid(pngPtr, infoPtr, PNG_INFO_tRNS)) 
	{
        png_set_tRNS_to_alpha(pngPtr);
        image->channels += 1;
    }

    if (image->bitDepth == 16)
        png_set_strip_16(pngPtr);

    //Allocate memory for data and raws
    image->rowPtrs = new png_bytep[image->height];
    image->data = new png_byte[image->width * image->height 
        * image->bitDepth * image->channels / 8]; //REVISE: channels?

    //Set pointer to beginning of each row
    const unsigned int stride = image->width * image->bitDepth 
        * image->channels / 8;
    for (size_t i = 0; i < image->height; i++) 
	{
        png_uint_32 q = i * stride;
        image->rowPtrs[i] = (png_bytep)image->data + q;
    }

    //Actually read data
    png_read_image(pngPtr, image->rowPtrs);

	//Read end
	png_read_end(pngPtr, infoPtr);

    png_destroy_read_struct(&pngPtr, &infoPtr, (png_infopp)0);
}

void writeData(std::ostream& source, Image *image)
{
	//Create write structure
	png_structp pngPtr = png_create_write_struct(
		PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	if (!pngPtr)
	{
		std::cout << "Cannot initialize write struct";
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
	if (setjmp(png_jmpbuf(pngPtr)));

	//Set custom read function (read from std::stream)
	png_set_write_fn(pngPtr, (png_voidp)&source, pngWriteData, pngFlushData);

	// Write header
	png_set_IHDR(pngPtr, infoPtr, image->width, image->height, image->bitDepth,
		image->colorType, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
		PNG_FILTER_TYPE_DEFAULT);

	png_write_info(pngPtr, infoPtr);

	// Write image data
	for (unsigned int i = 0; i < image->height; i++)
	{
		png_write_row(pngPtr, image->rowPtrs[i]);
	}

	// End write
	png_write_end(pngPtr, 0);

	if (infoPtr)
		png_free_data(pngPtr, infoPtr, PNG_FREE_ALL, -1);
	if (pngPtr)
		png_destroy_write_struct(&pngPtr, 0);
}

TextureResource::TextureResource(Renderer *renderer) :
	_renderer(renderer)
{
}

TextureResource::~TextureResource()
{
}

bool TextureResource::load(std::istream& in, Object *&resource) const
{
    Texture *texture = _renderer->createTexture();

	std::int16_t type = 0;
	std::int16_t filter = 0;
	std::int16_t wrap = 0;
	std::int16_t format = 0;
	std::int16_t aniso = 0;
	std::int16_t mipmap = 0;

	in.read((char *)&type, sizeof(std::int16_t));
	in.read((char *)&filter, sizeof(std::int16_t));
	in.read((char *)&wrap, sizeof(std::int16_t));
	in.read((char *)&format, sizeof(std::int16_t));
	in.read((char *)&aniso, sizeof(std::int16_t));
	in.read((char *)&mipmap, sizeof(std::int16_t));

	texture->setType(Texture::Type(type));
	texture->setFilter(Texture::Filter(filter));
	texture->setWrap(Texture::Wrap(wrap));
	texture->setFormat(Texture::Format(format));
	texture->setAnisotropicLevel(aniso);
	texture->setMipmapCount(mipmap);

	if (texture->type() == Texture::CubeMap)
	{
		Image *images = new Image[6];
		for (int i = 0; i < 6; ++i)
		{
			if (!validate(in))
				return false;

			texture->images[i] = images + i;
			readData(in, texture->images[i]);
		}
	}
	else
	{
		if (!validate(in))
			return false;

		texture->images[0] = new Image();
		readData(in, texture->images[0]);
	}

    resource = texture;
    return true;
}

bool TextureResource::save(std::ostream& out, Object *resource) const
{
	Texture *texture = static_cast<Texture *>(resource);
	if (!texture)
		return false;

	std::int16_t type = texture->type();
	std::int16_t filter = texture->filter();
	std::int16_t wrap = texture->wrap();
	std::int16_t format = texture->format();
	std::int16_t aniso = texture->anisotropicLevel();
	std::int16_t mipmap = texture->mipmapCount();

	out.write((char *)&type, sizeof(std::int16_t));
	out.write((char *)&filter, sizeof(std::int16_t));
	out.write((char *)&wrap, sizeof(std::int16_t));
	out.write((char *)&format, sizeof(std::int16_t));
	out.write((char *)&aniso, sizeof(std::int16_t));
	out.write((char *)&mipmap, sizeof(std::int16_t));

	if (texture->type() == Texture::CubeMap)
	{
		for (int i = 0; i < 6; ++i)
			writeData(out, texture->images[i]);
	}
	else
		writeData(out, texture->images[0]);

	return true;
}
