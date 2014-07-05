#ifndef FILERESOURCEIO_H
#define FILERESOURCEIO_H

#include <QObject>

#include "global.h"
#include "resourceio.h"

class ResourceGroup;

class FileResourceIO : public QObject, public ResourceIO
{
	Q_OBJECT
	
public:
	FileResourceIO(const std::string& basePath, const std::string& config = "resources.meta");
	~FileResourceIO();

	bool isReadOnly() const { return false; }

	ResourceGroup *rootGroup() const override;
	bool createSubGroup(ResourceGroup *baseGroup, const std::string& groupName) override;
	bool removeSubGroup(ResourceGroup *baseGroup) override;

	bool read(std::shared_ptr<BaseResource> loader, const std::string& id, Object *& object) override;
	bool write(std::shared_ptr<BaseResource> loader, const std::string& id, Object *object) override;

private:
	ResourceGroup *_root;
	std::string _configFile;

};

#endif