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

unsigned int toPngColorType(int type)
{
	switch (type)
	{
	case FIC_PALETTE:
		return 1; //Png palette
	case FIC_RGB:
		return 2; //Png rgb
	case FIC_RGBALPHA:
		return 4; //Png rgba
	default:
		return 4;
	}
}

void loadImage(const char *name, Image *image)
{
	FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(name);
	FIBITMAP *bitmap = FreeImage_Load(fif, name);

	if (!bitmap)
		return;

	image->width = FreeImage_GetWidth(bitmap);
	image->height = FreeImage_GetHeight(bitmap);
	image->bitDepth = FreeImage_GetBPP(bitmap);
	image->channels = 4;
	image->colorType = toPngColorType(FreeImage_GetColorType(bitmap));

	//Allocate memory for data and raws
	int dataSize = image->width * image->height * image->bitDepth * image->channels / 8;
	image->rowPtrs = new unsigned char *[image->height];
	image->data = new unsigned char[dataSize];

	//Set data
	unsigned char *imageData = FreeImage_GetBits(bitmap);
	memcpy(image->data, imageData, dataSize);

	//Set pointer to beginning of each row
	const unsigned int stride = image->width * image->bitDepth * image->channels / 8;
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
}

TextureImporter::~TextureImporter()
{

}

std::shared_ptr<Object> TextureImporter::import(const QString& filename, const QVariantMap& config /*= QVariantMap()*/)
{
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
    
	return texture;
}

QStringList TextureImporter::suffixes()
{
    return QStringList() << "bmp" << "png"
        << "jpeg" << "jpg" << "psd" << "gif";
}

QStringList TextureImporter::signatures()
{
    return QStringList();
}
