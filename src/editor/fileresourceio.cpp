#include "fileresourceio.h"
#include "resourcegroup.h"

#include <QDir>
#include <QMap>

#include <map>
#include <fstream>

class FileResourceGroup : public ResourceGroup
{
public:
	FileResourceGroup(const QString& path,
		FileResourceGroup *parent = nullptr) :
		_path(path), _parent(parent) {}
	~FileResourceGroup() {}

	ResourceGroup *parent() const override
	{
		return _parent;
	}

	ResourceGroup *group(const std::string& id) const override
	{
		return _subfolders.value(QString::fromStdString(id), nullptr);
	}

	FileResourceGroup *_parent;
	QDir _path;
	QMap<QString, FileResourceGroup *> _subfolders;

};

FileResourceIO::FileResourceIO(const std::string& basePath, const std::string& config) :
	ResourceIO(basePath),
	_root(nullptr),
	_configFile(config)
{
	QString qBasePath = QString::fromStdString(basePath);
	QDir baseDir(qBasePath);
	if (baseDir.exists())
		_root = new FileResourceGroup(qBasePath);
}

FileResourceIO::~FileResourceIO()
{
}

ResourceGroup *FileResourceIO::rootGroup() const
{
	return _root;
}

bool FileResourceIO::createSubGroup(ResourceGroup *baseGroup, const std::string& groupName)
{
	//TODO: create full path
	FileResourceGroup *group = dynamic_cast<FileResourceGroup *>(baseGroup);
	if (!group)
		return false;

	QString qGroupName = QString::fromStdString(groupName);
	FileResourceGroup *subGroup = 
		group->_subfolders.value(qGroupName, nullptr);
	//Already exist
	if (subGroup)
		return true;

	//Try to create new sub folder
	if (group->_path.mkdir(qGroupName))
	{
		subGroup = new FileResourceGroup(qGroupName, group);
		group->_subfolders.insert(qGroupName, subGroup);

		return true;
	}
	
	return false;
}

bool FileResourceIO::removeSubGroup(ResourceGroup *baseGroup)
{
	FileResourceGroup *group = dynamic_cast<FileResourceGroup *>(baseGroup);
	//Wrong group type
	if (!group)
		return false;

	FileResourceGroup *parent = dynamic_cast<FileResourceGroup *>(group->parent());
	//Cannot remove root group
	if (!parent)
		return false;

	QString groupKey = parent->_subfolders.key(group);
	group->_path.removeRecursively();
	parent->_subfolders.remove(groupKey);
	delete group;

	return false;
}

bool FileResourceIO::read(std::shared_ptr<BaseResource> loader, const std::string& id, Object *& object)
{
	std::ifstream in(basePath() + '/' + id, std::ios::in | std::ios::binary);
	if (!in.good())
		return false;

	return loader->load(in, object);
}

bool FileResourceIO::write(std::shared_ptr<BaseResource> loader, const std::string& id, Object *object)
{
	std::ofstream out(basePath() + '/' + id, std::ios::out | std::ios::binary);
	if (!out.good())
		return false;

	return loader->save(out, object);
}
