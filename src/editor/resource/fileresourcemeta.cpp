#include "fileresourcemeta.h"

#include <yaml-cpp/yaml.h>

FileResourceMeta::FileResourceMeta(const QString& config, QObject *parent) :
	QObject(parent),
	_config(_config)
{
}

FileResourceMeta::~FileResourceMeta()
{
}

FileResourceGroup *FileResourceMeta::read() const
{
	return nullptr;
}

void FileResourceMeta::write(FileResourceGroup *)
{

}