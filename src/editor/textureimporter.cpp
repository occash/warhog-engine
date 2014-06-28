#include "textureimporter.h"
#include <texture.h>
#include <resource/textureresource.h>
#include <resourcemanager.h>

#include <memory>
#include <Freeimage.h>

TextureImporter::TextureImporter(QObject *parent)
    : Importer(parent)
{
}

TextureImporter::~TextureImporter()
{

}

void TextureImporter::import(const QString& filename)
{
    int sep = filename.lastIndexOf('/');
    QString shortName = filename.mid(sep + 1);
    QStringList nameExt = shortName.split('.');
    QByteArray nameBytes = filename.toLocal8Bit();

    FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(nameBytes.constData());
    FIBITMAP *image = FreeImage_Load(fif, nameBytes.constData());

    std::shared_ptr<Texture> texture(new Texture());
    texture->_width = FreeImage_GetWidth(image);
    texture->_height = FreeImage_GetHeight(image);
    texture->_bitDepth = FreeImage_GetBPP(image); //Bit depth?
    texture->_colorType/* = FreeImage_GetColorType(image)*/;//Convert to png
    //texture->_channels;
    texture->_data = FreeImage_GetBits(image);
    //texture->_rowPtrs;
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
