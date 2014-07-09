#ifndef FILERESOURCEIO_H
#define FILERESOURCEIO_H

#include <QObject>

#include "resourceio.h"

class ResourceNode;

class FileResourceIO : public QObject, public ResourceIO
{
	Q_OBJECT
	
public:
	FileResourceIO(const std::string& basePath, const std::string& config = "resources.meta");
	~FileResourceIO();

	bool readOnly() const override;

	bool createTree(const std::string& path, ResourceNode *& root) override;
	bool removeTree(ResourceNode *root) override;

	bool createGroup(ResourceNode *baseNode, const std::string& id) override;
	bool createHandle(ResourceNode *baseNode, BaseResource::Type type, const std::string& id) override;
	bool removeNode(ResourceNode *baseNode) override;

	bool read(ResourceNode *node, std::shared_ptr<BaseResource> loader, Object *& object) override;
	bool write(ResourceNode *node, std::shared_ptr<BaseResource> loader, Object *object) override;

private:
	ResourceNode *_root;
	std::string _configFile;

};

#endif