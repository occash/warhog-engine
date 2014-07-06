#include "fileresourceio.h"
#include "resourcegroup.h"

#include <QDir>
#include <QMap>
#include <QList>
#include <QStack>
#include <QJsonDocument>
#include <QJsonObject>
#include <yaml-cpp/yaml.h>

#include <map>
#include <fstream>
#include <iostream>

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

	std::string name() const override
	{
		return QDir(_path).dirName().toStdString();
	}

	std::list<std::string> groupNames() const
	{
		return _subfolders.keys();
	}

	ResourceGroup *group(const std::string& id) const override
	{
		return _subfolders.value(QString::fromStdString(id), nullptr);
	}

	FileResourceGroup *_parent;
	QString _path;
	QMap<QString, FileResourceGroup *> _subfolders;

};

FileResourceIO::FileResourceIO(const std::string& basePath, const std::string& config) :
	ResourceIO(basePath),
	_root(nullptr),
	_configFile(config)
{
	YAML::Node rootNode = YAML::LoadFile("config.yaml");
	YAML::Node parentNode = rootNode["bundle"];
	QStack<YAML::Node> parents;
	parents.push(parentNode);

	QStack<FileResourceGroup *> groups;
	groups.push(nullptr);
	while (!parents.isEmpty())
	{
		YAML::Node current = parents.pop();
		FileResourceGroup *parent = groups.pop();
		FileResourceGroup *newGroup =
			new FileResourceGroup(
			QString::fromStdString(current["path"].as<std::string>()),
			parent);
		if (parent)
			parent->_subfolders[QString::fromStdString(newGroup->name())] = newGroup;
		else
			_root = newGroup;

		YAML::Node subfolders = current["subfolders"];
		if (subfolders && subfolders.IsMap())
		{
			auto i = subfolders.begin();
			for (; i != subfolders.end(); ++i)
			{
				parents.push(subfolders[i->first.as<std::string>()]);
				groups.push(newGroup);
			}
		}
	}
}

FileResourceIO::~FileResourceIO()
{
	FileResourceGroup *root = 
		dynamic_cast<FileResourceGroup *>(_root);
	if (root->_subfolders.isEmpty())
		return;

	YAML::Node rootNode;
	rootNode["version"] = 1.0;
	YAML::Node parentNode = rootNode["bundle"];
	QStack<YAML::Node> parents;
	parents.push(parentNode);

	QStack<FileResourceGroup *> groups;
	groups.push(root);

	while (!groups.isEmpty())
	{
		FileResourceGroup *current = groups.pop();
		YAML::Node currentParent = parents.pop();

		YAML::Node node;
		node["name"] = current->name();
		node["path"] = current->_path.toStdString();
		if (current->_parent)
			currentParent["subfolders"][current->name()] = node;
		else
			parentNode = node;

		if (current->_subfolders.size())
		{
			node["subfolders"] = YAML::Node(YAML::NodeType::Map);
			for (auto i = current->_subfolders.begin();
				i != current->_subfolders.end(); ++i)
			{
				groups.push(i.value());
				parents.push(node);
			}
		}
	}

	std::ofstream fout("config.yaml");
	fout << rootNode;
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
	if (QDir(group->_path + "/" + qGroupName).exists() ||
		QDir(group->_path).mkdir(qGroupName))
	{
		subGroup = new FileResourceGroup(group->_path + "/" + qGroupName, group);
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
	if (groupKey.isEmpty())
		return false;

	QDir(group->_path).removeRecursively();
	parent->_subfolders.remove(groupKey);
	delete group;

	return true;
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
