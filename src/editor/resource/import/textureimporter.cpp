#include "textureimporter.h"
#include <texture.h>
#include <resource/textureresource.h>
#include <resourcemanager.h>

#include <memory>
#include <Freeimage.h>

static QString cubeNames[] = 
{
	"_negx",
	"_posx",
	"_negy",
	"_posy",
	"_negz",
	"_posz"
};

unsigned int calculateColorType(FIBITMAP *bitmap)
{
	FREE_IMAGE_COLOR_TYPE type = FreeImage_GetColorType(bitmap);
	switch (type)
	{
	case FIC_MINISBLACK:
		return 0; //Png gray
	case FIC_RGB:
		return 2; //Png rgb
	case FIC_PALETTE:
		return 2 | 1; //Png palette
	case FIC_RGBALPHA:
		return 2 | 4; //Png rgba
	default:
		return 2 | 4;
	}
}

unsigned int typeToSize(FREE_IMAGE_TYPE imageType)
{
	switch (imageType)
	{
	case FIT_UNKNOWN:
		return 0;
	case FIT_BITMAP:
		return sizeof(BYTE) * 8;
	case FIT_UINT16:
	case FIT_INT16:
	case FIT_RGB16:
	case FIT_RGBA16:
		return sizeof(WORD) * 8;
	case FIT_UINT32:
	case FIT_INT32:
		return sizeof(DWORD) * 8;
	case FIT_FLOAT:
	case FIT_RGBF:
	case FIT_RGBAF:
		return sizeof(float) * 8;
	case FIT_DOUBLE:
		return sizeof(double) * 8;
	case FIT_COMPLEX:
		return sizeof(FICOMPLEX) * 8;
	default:
		return 0;
	}
}

void calculateDepth(FIBITMAP *bitmap, unsigned int *bitDepth, unsigned int *channels)
{
	//Set bith depth
	FREE_IMAGE_TYPE imageType = FreeImage_GetImageType(bitmap);
	unsigned int bitSize = typeToSize(imageType);
	*bitDepth = bitSize;

	//Set number of channels
	unsigned int bitsPerPixel = FreeImage_GetBPP(bitmap);
	*channels = bitsPerPixel / bitSize;
}

void loadImage(const char *name, Image *image)
{
	FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(name);
	FIBITMAP *bitmap = FreeImage_Load(fif, name);

	if (!bitmap)
		return;

	image->width = FreeImage_GetWidth(bitmap);
	image->height = FreeImage_GetHeight(bitmap);
	calculateDepth(bitmap, &image->bitDepth, &image->channels);
	image->colorType = calculateColorType(bitmap);

	//Allocate memory for data and raws
	int dataSize = image->width * image->height * image->bitDepth * image->channels / 8;
	image->rowPtrs = new unsigned char *[image->height];
	image->data = new unsigned char[dataSize];

	//Set data
	unsigned char *imageData = FreeImage_GetBits(bitmap);
	memcpy(image->data, imageData, dataSize);

	//Set pointer to beginning of each row
	const unsigned int stride = image->width * image->channels;
	for (size_t i = 0; i < image->height; i++)
	{
		unsigned int q = i * stride;
		image->rowPtrs[i] = image->data + q;
	}

	FreeImage_Unload(bitmap);
}

TextureImporter::TextureImporter(QObject *parent)
    : Importer(parent)
{
	FreeImage_Initialise();
}

TextureImporter::~TextureImporter()
{
	FreeImage_DeInitialise();
}

std::shared_ptr<Object> TextureImporter::import(const QString& filename, const QVariantMap& config /*= QVariantMap()*/)
{
	emit progress(0);
    int sep = filename.lastIndexOf('/');
    QString shortName = filename.mid(sep + 1);
    QStringList nameExt = shortName.split('.');
    QByteArray nameBytes = filename.toLocal8Bit();

	QString pattern;
	bool isCube = false;
	for (int i = 0; i < 6; ++i)
	{
		if (shortName.contains(cubeNames[i]))
		{
			pattern = cubeNames[i];
			isCube = true;
			break;
		}
	}

	std::shared_ptr<Texture> texture(new Texture());

	if (isCube)
	{
		texture->setType(Texture::CubeMap);

		Image *images = new Image[6];
		for (int i = 0; i < 6; ++i)
		{
			QString fullName = filename;
			QString cubeName = fullName.replace(pattern, cubeNames[i]);
			QByteArray cubeNameBytes = cubeName.toLocal8Bit();
			texture->images[i] = images + i;
			loadImage(cubeNameBytes.constData(), texture->images[i]);
		}
	}
	else
	{
		texture->images[0] = new Image();
		loadImage(nameBytes.constData(), texture->images[0]);
	}

	emit progress(100);
    
	return texture;
}

QStringList TextureImporter::suffixes()
{
    return QStringList() << "bmp" << "png"
        << "jpeg" << "jpg" << "psd" << "gif";
}
