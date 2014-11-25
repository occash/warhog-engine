#include "fileresourceio.h"
#include <fileresourcemeta.h>

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
	FileResourceHandle(
		BaseResource::Type type,
		const QString& name,
		ResourceNode *parent = nullptr) :
		_name(name), _parent(parent), _type(type) {}
	~FileResourceHandle() {}

public:
	std::string name() const override
	{
		return _name.toStdString();
	}

	bool valid() const override
	{
		return QFileInfo::exists(_name);
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
	BaseResource::Type _type;
	QString _name;
	ResourceNode *_parent;

};

class FileResourceGroup : public ResourceGroup
{
public:
	FileResourceGroup(
		const QString& name,
		ResourceNode *parent = nullptr) :
		_name(name), _parent(parent) {}
	~FileResourceGroup() 
	{
		qDeleteAll(_subfolders);
		_subfolders.clear();
	}

public:
	std::string name() const override
	{
		return _name.toStdString();
	}

	bool valid() const override
	{
		return QDir(_name).exists();
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
	QString _name;
	QMap<QString, ResourceNode *> _subfolders;

};

FileResourceIO::FileResourceIO() :
	ResourceIO(),
	_meta(new FileResourceMeta(this))
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
	QString id = QDir(qPath).dirName();
	qPath = QDir(qPath).absoluteFilePath("resources.meta");

	if (!QFileInfo(qPath).exists())
	{
		root = createGroup(nullptr, id.toStdString());
		return true;
	}

	return _meta->readTree(qPath.toStdString(), root);
}

bool FileResourceIO::removeTree(ResourceNode *root)
{
	QString qPath = QString::fromStdString(basePath());
	qPath = QDir(qPath).absoluteFilePath("resources.meta");

	bool result = _meta->writeTree(qPath.toStdString(), root);
	
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

	QString path = fullPath(group);

	//Try to create new sub folder
	if (QDir(path + "/" + qGroupName).exists() ||
		QDir(path).mkdir(qGroupName))
	{
		subGroup = new FileResourceGroup(qGroupName, group);
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

	QString qHandleName = QString::fromStdString(id);
	ResourceNode *subNode =
		group->_subfolders.value(qHandleName, nullptr);
	//Already exist
	if (subNode)
		return subNode;

	QString path = fullPath(group);

	//Try to create new file
	QString filePath = path + "/" + qHandleName;
	if (QFile(filePath).exists() ||
		QFile(filePath).open(QIODevice::WriteOnly))
	{
		subNode = new FileResourceHandle(type, qHandleName, group);
		group->_subfolders.insert(qHandleName, subNode);

		return subNode;
	}

	return nullptr;
}

bool FileResourceIO::removeNode(ResourceNode *node)
{
	FileResourceGroup *parent = dynamic_cast<FileResourceGroup *>(node->parent());
	//Cannot remove root group
	if (!parent)
		return false;

	QString groupKey = parent->_subfolders.key(node);
	if (groupKey.isEmpty())
		return false;

	QString path = fullPath(node);
	if (node->nodeType() == ResourceNode::NodeType::Group)
	{
		FileResourceGroup *group = dynamic_cast<FileResourceGroup *>(node);
		//Wrong node type
		if (!group)
			return false;

		QDir(path).removeRecursively();
		parent->_subfolders.remove(groupKey);
		delete group;

		return true;
	}
	else if (node->nodeType() == ResourceNode::NodeType::Handle)
	{
		FileResourceHandle *handle = dynamic_cast<FileResourceHandle *>(node);
		//Wrong node type
		if (!handle)
			return false;

		QFile(path).remove();
		parent->_subfolders.remove(groupKey);
		delete handle;

		return true;
	}

	return false;
}

bool FileResourceIO::renameNode(ResourceNode *node, const std::string& id)
{
	/*if (!node->valid())
		return false;*/

	QString path = fullPath(node);

	QString qId = QString::fromStdString(id);

	if (node->nodeType() == ResourceNode::NodeType::Group)
	{
		FileResourceGroup *group =
			dynamic_cast<FileResourceGroup *>(node);
		if (!group)
			return false;

		QDir dir(path);
		QString oldId = dir.dirName();
		dir.cdUp();
		if (dir.rename(oldId, qId))
		{
			group->_name = qId;
			return true;
		}
	}
	else if (node->nodeType() == ResourceNode::NodeType::Handle)
	{
		FileResourceHandle *handle =
			dynamic_cast<FileResourceHandle *>(node);
		if (!handle)
			return false;

		if (QDir().rename(path, qId))
		{
			handle->_name = qId;
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

	QString path = fullPath(node);

	if (!QFileInfo(path).exists())
		return false;

	std::string id = path.toStdString();
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

	QString path = fullPath(node);

	if (!QFileInfo(path).exists())
		return false;

	std::string id = path.toStdString();
	std::ofstream out(id, std::ios::out | std::ios::binary);
	if (!out.good())
		return false;

	return loader->save(out, object);
}

QString FileResourceIO::fullPath(ResourceNode *node)
{
	QString groupPath;
	while (node && node != rootNode())
	{
		QString gp = "/" + QString::fromStdString(node->name());
		groupPath.prepend(gp);
		node = dynamic_cast<FileResourceGroup *>(node->parent());
	}

	QString path = QString::fromStdString(basePath());
	path += groupPath;

	return path;
}
