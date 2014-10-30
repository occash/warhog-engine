#ifndef FILERESOURCEMETA_H
#define FILERESOURCEMETA_H

#include <QObject>
#include <memory>

class ResourceNode;
class ResourceIO;

class FileResourceMeta : public QObject
{
public:
	FileResourceMeta(ResourceIO *io, QObject *parent = nullptr);
	~FileResourceMeta();

	bool readTree(const QString& meta, ResourceNode *& root);
	bool writeTree(const QString& meta, ResourceNode *root);

private:
	ResourceIO *_io;
	QString _metafile;

};

#endif