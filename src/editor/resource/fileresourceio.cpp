#include "fileresourceio.h"
#include "fileresourcemeta.h"

#include <resourcegroup.h>

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QMap>
#include <QList>
#include <QUrl>

#include <yaml-cpp/yaml.h>
#include <fstream>

class FileResourceHandle : public ResourceHandle
{
public:
	FileResourceHandle(BaseResource::Type type,
		const QString& path,
		ResourceNode *parent = nullptr) :
		_path(path), _parent(parent), _type(type) {}
	~FileResourceHandle() {}

public:
	std::string name() const override
	{
		return QFileInfo(_path).fileName().toStdString();
	}

	bool valid() const override
	{
		return QFileInfo::exists(_path);
	}

	ResourceNode *parent() const override
	{
		return _parent;
	}

	int childCount() const override
	{
		return 0;
	}

	ResourceNode *child(int index) const override
	{
		return nullptr;
	}

	ResourceNode *child(const std::string& id) const override
	{
		return nullptr;
	}

	BaseResource::Type type() const override
	{
		return _type;
	}

public:
	ResourceNode *_parent;
	QString _path;
	BaseResource::Type _type;

};

class FileResourceGroup : public ResourceGroup
{
public:
	FileResourceGroup(const QString& path,
		ResourceNode *parent = nullptr) :
		_path(path), _parent(parent) {}
	~FileResourceGroup() 
	{
		qDeleteAll(_subfolders);
		_subfolders.clear();
	}

public:
	std::string name() const override
	{
		return QDir(_path).dirName().toStdString();
	}

	bool valid() const override
	{
		return QDir(_path).exists();
	}

	ResourceNode *parent() const override
	{
		return static_cast<ResourceNode *>(_parent);
	}

	int childCount() const override
	{
		return _subfolders.size();
	}

	ResourceNode *child(int index) const override
	{
		QString key(_subfolders.keys().at(index));
		return _subfolders.value(key, nullptr);
	}

	ResourceNode *child(const std::string& id) const override
	{
		return _subfolders.value(QString::fromStdString(id), nullptr);
	}

public:
	ResourceNode *_parent;
	QString _path;
	QMap<QString, ResourceNode *> _subfolders;

};

FileResourceIO::FileResourceIO() :
	ResourceIO(),
	_meta(new FileResourceMeta(this, this))
{
}

FileResourceIO::~FileResourceIO()
{
}

bool FileResourceIO::readOnly() const
{
	return false;
}

bool FileResourceIO::createTree(const std::string& path, ResourceNode *& root)
{
	QString qPath = QString::fromStdString(path);
	qPath = QDir(qPath).absoluteFilePath("resources.meta");

	if (!QFileInfo(qPath).exists())
	{
		root = createGroup(nullptr, path);
		return true;
	}

	return _meta->readTree(qPath, root);
}

bool FileResourceIO::removeTree(ResourceNode *root)
{
	QString qPath = QString::fromStdString(basePath());
	qPath = QDir(qPath).absoluteFilePath("resources.meta");

	bool result = _meta->writeTree(qPath, root);
	
	delete root;
	return true;
}

ResourceNode *FileResourceIO::createGroup(ResourceNode *baseNode, const std::string& id)
{
	if (!baseNode)
		return new FileResourceGroup(QString::fromStdString(id));

	//Can create only in group
	if (baseNode->nodeType() != ResourceNode::NodeType::Group)
		return nullptr;

	//TODO: create full path
	FileResourceGroup *group = dynamic_cast<FileResourceGroup *>(baseNode);
	if (!group)
		return nullptr;

	QString qGroupName = QString::fromStdString(id);
	ResourceNode *subGroup = 
		group->_subfolders.value(qGroupName, nullptr);
	//Already exist
	if (subGroup)
		return subGroup;

	//Try to create new sub folder
	if (QDir(group->_path + "/" + qGroupName).exists() ||
		QDir(group->_path).mkdir(qGroupName))
	{
		subGroup = new FileResourceGroup(group->_path + "/" + qGroupName, group);
		group->_subfolders.insert(qGroupName, subGroup);

		return subGroup;
	}
	
	return nullptr;
}

ResourceNode *FileResourceIO::createHandle(ResourceNode *baseNode, BaseResource::Type type, const std::string& id)
{
	if (!baseNode)
		return nullptr;

	//Can create only in group
	if (baseNode->nodeType() != ResourceNode::NodeType::Group)
		return nullptr;

	//TODO: create full path
	FileResourceGroup *group = dynamic_cast<FileResourceGroup *>(baseNode);
	if (!group)
		return nullptr;

	QString qGroupName = QString::fromStdString(id);
	ResourceNode *subGroup =
		group->_subfolders.value(qGroupName, nullptr);
	//Already exist
	if (subGroup)
		return subGroup;

	//Try to create new file
	QString filePath = group->_path + "/" + qGroupName;
	if (QFile(filePath).exists() ||
		QFile(filePath).open(QIODevice::WriteOnly))
	{
		subGroup = new FileResourceHandle(type, group->_path + "/" + qGroupName, group);
		group->_subfolders.insert(qGroupName, subGroup);

		return subGroup;
	}

	return nullptr;
}

bool FileResourceIO::removeNode(ResourceNode *baseNode)
{
	if (baseNode->nodeType() == ResourceNode::NodeType::Group)
	{
		FileResourceGroup *group = dynamic_cast<FileResourceGroup *>(baseNode);
		//Wrong group type
		if (!group)
			return false;

		FileResourceGroup *parent = dynamic_cast<FileResourceGroup *>(group->parent());
		//Cannot remove root group
		if (!parent)
			return false;

		QString groupKey = parent->_subfolders.key(group);
		if (groupKey.isEmpty())
			return false;

		QDir(group->_path).removeRecursively();
		parent->_subfolders.remove(groupKey);
		delete group;

		return true;
	}
	else if (baseNode->nodeType() == ResourceNode::NodeType::Handle)
	{
		FileResourceHandle *handle = dynamic_cast<FileResourceHandle *>(baseNode);
		//Wrong group type
		if (!handle)
			return false;

		FileResourceGroup *parent = dynamic_cast<FileResourceGroup *>(handle->parent());
		//Cannot remove root group
		if (!parent)
			return false;

		QString groupKey = parent->_subfolders.key(handle);
		if (groupKey.isEmpty())
			return false;

		QFile(handle->_path).remove();
		parent->_subfolders.remove(groupKey);
		delete handle;

		return true;
	}

	return false;
}

bool FileResourceIO::renameNode(ResourceNode *node, const std::string& id)
{
	if (!node->valid())
		return false;

	if (node->nodeType() == ResourceNode::NodeType::Group)
	{
		FileResourceGroup *group =
			dynamic_cast<FileResourceGroup *>(node);
		if (!group)
			return false;

		QDir dir(group->_path);
		QString dirName = dir.dirName();
		QString dirPath = dir.absolutePath();
		dirPath.chop(dirName.size());
		dirPath.append(QString::fromStdString(id));
		if (dir.rename(group->_path, dirPath))
		{
			group->_path = dirPath;
			return true;
		}
	}
	else if (node->nodeType() == ResourceNode::NodeType::Handle)
	{
		FileResourceHandle *handle =
			dynamic_cast<FileResourceHandle *>(node);
		if (!handle)
			return false;

		QString newPath = QFileInfo(handle->_path).dir().absolutePath();
		newPath.append("/");
		newPath.append(QString::fromStdString(id));
		if (QDir().rename(handle->_path, newPath))
		{
			handle->_path = newPath;
			return true;
		}
	}

	return false;
}

bool FileResourceIO::read(ResourceNode *node, std::shared_ptr<BaseResource> loader, Object *& object)
{
	if (node->nodeType() != ResourceNode::NodeType::Handle)
		return false;

	FileResourceHandle *handle = dynamic_cast<FileResourceHandle *>(node);
	if (!handle)
		return false;

	if (QFileInfo(handle->_path).exists())
		return false;

	std::string id = handle->_path.toStdString();
	std::ifstream in(id, std::ios::in | std::ios::binary);
	if (!in.good())
		return false;

	return loader->load(in, object);
}

bool FileResourceIO::write(ResourceNode *node, std::shared_ptr<BaseResource> loader, Object *object)
{
	if (node->nodeType() != ResourceNode::NodeType::Handle)
		return false;

	FileResourceHandle *handle = dynamic_cast<FileResourceHandle *>(node);
	if (!handle)
		return false;

	if (!QFileInfo(handle->_path).exists())
		return false;

	std::string id = handle->_path.toStdString();
	std::ofstream out(id, std::ios::out | std::ios::binary);
	if (!out.good())
		return false;

	return loader->save(out, object);
}
