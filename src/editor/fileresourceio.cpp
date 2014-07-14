#include "fileresourceio.h"
#include "resourcegroup.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QMap>
#include <QList>
#include <QStack>
#include <QUrl>
#include <yaml-cpp/yaml.h>

#include <map>
#include <fstream>
#include <iostream>

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

	/*int groupCount() const override
	{
		return _subfolders.size();
	}

	std::list<std::string> groupNames() const override
	{
		QStringList keys = _subfolders.keys();
		std::list<std::string> result;
		std::transform(
			keys.begin(), 
			keys.end(), 
			result.begin(),
			[](const QString& in) { return in.toStdString(); }
			);
		return result;
	}*/

	ResourceGroup *group(const std::string& id) const override
	{
		ResourceNode *node = _subfolders.value(QString::fromStdString(id), nullptr);
		if (!node || node->nodeType() != ResourceNode::NodeType::Group)
			return nullptr;
		return static_cast<ResourceGroup *>(node);
	}

	/*virtual int resourceCount() const override
	{
		return 0;
	}

	std::list<std::string> resourceNames() const override
	{
		return std::list<std::string>();
	}*/

	ResourceHandle *resource(const std::string& id) const override
	{
		ResourceNode *node = _subfolders.value(QString::fromStdString(id), nullptr);
		if (!node || node->nodeType() != ResourceNode::NodeType::Handle)
			return nullptr;
		return static_cast<ResourceHandle *>(node);
	}

public:
	ResourceNode *_parent;
	QString _path;
	QMap<QString, ResourceNode *> _subfolders;

};

FileResourceIO::FileResourceIO() :
	ResourceIO()
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
		root = new FileResourceGroup(qPath);
		return true;
	}

	YAML::Node rootNode = YAML::LoadFile(qPath.toStdString());
	YAML::Node parentNode = rootNode["bundle"];
	QStack<YAML::Node> parents;
	parents.push(parentNode);

	QStack<ResourceNode *> groups;
	groups.push(nullptr);
	while (!parents.isEmpty())
	{
		YAML::Node current = parents.pop();
		ResourceNode *parent = groups.pop();
		FileResourceGroup *parentGroup = dynamic_cast<FileResourceGroup *>(parent);
		ResourceNode *currentNode = nullptr;

		ResourceNode::NodeType nodeType =
			static_cast<ResourceNode::NodeType>(current["node"].as<int>());
		if (nodeType == ResourceNode::NodeType::Group)
		{
			FileResourceGroup *newGroup =
				new FileResourceGroup(
				QString::fromStdString(current["path"].as<std::string>()),
				parentGroup
				);
			if (parentGroup)
				parentGroup->_subfolders[QString::fromStdString(newGroup->name())] = newGroup;
			else
				root = newGroup;

			currentNode = newGroup;
		}
		else if (nodeType == ResourceNode::NodeType::Handle)
		{
			if (!parentGroup)
				continue;

			FileResourceHandle *newHandle =
				new FileResourceHandle(
				static_cast<BaseResource::Type>(current["type"].as<int>()),
				QString::fromStdString(current["path"].as<std::string>()),
				parentGroup
				);
			parentGroup->_subfolders[QString::fromStdString(newHandle->name())] = newHandle;

			currentNode = newHandle;
		}

		YAML::Node subfolders = current["children"];
		if (subfolders && subfolders.IsMap())
		{
			auto i = subfolders.begin();
			for (; i != subfolders.end(); ++i)
			{
				parents.push(subfolders[i->first.as<std::string>()]);
				groups.push(currentNode);
			}
		}
	}

	return true;
}

bool FileResourceIO::removeTree(ResourceNode *root)
{
	if (root->childCount() <= 0)
	{
		delete root;
		return true;
	}

	YAML::Node rootNode;
	rootNode["version"] = 2;
	YAML::Node parentNode = rootNode["bundle"];
	QStack<YAML::Node> parents;
	parents.push(parentNode);

	QStack<ResourceNode *> groups;
	groups.push(root);

	while (!groups.isEmpty())
	{
		ResourceNode *current = groups.pop();
		YAML::Node currentParent = parents.pop();

		YAML::Node node;
		node["name"] = current->name();
		node["node"] = static_cast<int>(current->nodeType());

		if (current->nodeType() == ResourceNode::NodeType::Group)
		{
			FileResourceGroup *group = 
				dynamic_cast<FileResourceGroup *>(current);
			node["path"] = group->_path.toStdString();
		}
		else if (current->nodeType() == ResourceNode::NodeType::Handle)
		{
			FileResourceHandle *handle =
				dynamic_cast<FileResourceHandle *>(current);
			node["path"] = handle->_path.toStdString();
			node["type"] = static_cast<int>(handle->type());
		}

		if (current->parent())
			currentParent["children"][current->name()] = node;
		else
			parentNode = node;

		if (current->childCount() > 0)
		{
			node["children"] = YAML::Node(YAML::NodeType::Map);
			for (int i = 0; i < current->childCount(); ++i)
			{
				groups.push(current->child(i));
				parents.push(node);
			}
		}
	}

	std::string outPath = basePath() + "/" + "resources.meta";
	std::ofstream fout(outPath);
	if (!fout)
	{
		delete root;
		return false;
	}

	fout << rootNode;
	delete root;
	return true;
}

bool FileResourceIO::createGroup(ResourceNode *baseNode, const std::string& id)
{
	//Can create only in group
	if (baseNode->nodeType() != ResourceNode::NodeType::Group)
		return false;

	//TODO: create full path
	FileResourceGroup *group = dynamic_cast<FileResourceGroup *>(baseNode);
	if (!group)
		return false;

	QString qGroupName = QString::fromStdString(id);
	ResourceNode *subGroup = 
		group->_subfolders.value(qGroupName, nullptr);
	//Already exist
	if (subGroup)
		return true;

	//Try to create new sub folder
	if (QDir(group->_path + "/" + qGroupName).exists() ||
		QDir(group->_path).mkdir(qGroupName))
	{
		subGroup = new FileResourceGroup(group->_path + "/" + qGroupName, group);
		group->_subfolders.insert(qGroupName, subGroup);

		return true;
	}
	
	return false;
}

bool FileResourceIO::createHandle(ResourceNode *baseNode, BaseResource::Type type, const std::string& id)
{
	//Can create only in group
	if (baseNode->nodeType() != ResourceNode::NodeType::Group)
		return false;

	//TODO: create full path
	FileResourceGroup *group = dynamic_cast<FileResourceGroup *>(baseNode);
	if (!group)
		return false;

	QString qGroupName = QString::fromStdString(id);
	ResourceNode *subGroup =
		group->_subfolders.value(qGroupName, nullptr);
	//Already exist
	if (subGroup)
		return true;

	//Try to create new file
	QString filePath = group->_path + "/" + qGroupName;
	if (QFile(filePath).exists() ||
		QFile(filePath).open(QIODevice::WriteOnly))
	{
		subGroup = new FileResourceHandle(type, group->_path + "/" + qGroupName, group);
		group->_subfolders.insert(qGroupName, subGroup);

		return true;
	}

	return false;
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

	if (QFileInfo(handle->_path).exists())
		return false;

	std::string id = handle->_path.toStdString();
	std::ofstream out(id, std::ios::out | std::ios::binary);
	if (!out.good())
		return false;

	return loader->save(out, object);
}
