#ifndef FILERESOURCEMETA_H
#define FILERESOURCEMETA_H

#include <QObject>
#include <memory>

class ResourceNode;
class ResourceIO;

class FileResourceMeta
{
public:
	FileResourceMeta(ResourceIO *io);
	~FileResourceMeta();

	bool readTree(const std::string & meta, ResourceNode *& root);
	bool writeTree(const std::string & meta, ResourceNode *root);

private:
	ResourceIO *_io;
	std::string _metafile;

};

#endif