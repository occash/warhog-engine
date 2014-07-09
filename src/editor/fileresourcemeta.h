#ifndef FILERESOURCEMETA_H
#define FILERESOURCEMETA_H

#include <QObject>

class FileResourceGroup;

class FileResourceMeta : public QObject
{
public:
	FileResourceMeta(const QString& config, QObject *parent = nullptr);
	~FileResourceMeta();

	FileResourceGroup *read() const;
	void write(FileResourceGroup *root);

private:
	QString _config;

};

#endif