#include "fileresourcemeta.h"
#include "fileresourceio.h"

#include <resourcegroup.h>

#include <QStack>
#include <fstream>

#include <stack>
#include <yaml-cpp/yaml.h>

using namespace std;

FileResourceMeta::FileResourceMeta(ResourceIO *io) : _io(io)
{
}

FileResourceMeta::~FileResourceMeta()
{
}

bool FileResourceMeta::readTree(const std::string& meta, ResourceNode *& root)
{
	YAML::Node rootNode = YAML::LoadFile(meta);
	YAML::Node parentNode = rootNode["bundle"];

	stack<YAML::Node> parents;
	parents.push(parentNode);

	stack<ResourceNode *> groups;
	groups.push(nullptr);

	while (!parents.empty()) {
		YAML::Node current = parents.top();
		parents.pop();

		ResourceNode *parent = groups.top();
		groups.pop();
		ResourceNode *currentNode = nullptr;


		ResourceNode::NodeType nodeType =
			static_cast<ResourceNode::NodeType>(current["node"].as<int>());
		std::string nodeName = current["name"].as<std::string>();
		if (nodeType == ResourceNode::NodeType::Group)
		{
			ResourceNode *newGroup = _io->createGroup(parent, nodeName);
			if (!parent)
				root = newGroup;

			currentNode = newGroup;
		}
		else if (nodeType == ResourceNode::NodeType::Handle)
		{
			if (!parent)
				continue;

			std::string handleType = current["type"].as<std::string>();
			ResourceNode *newHandle = _io->createHandle(parent, handleType, nodeName);

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

bool FileResourceMeta::writeTree(const std::string & meta, ResourceNode *root)
{
	YAML::Node rootNode;
	rootNode["version"] = 1;
	YAML::Node parentNode = rootNode["bundle"];
	stack<YAML::Node> parents;
	parents.push(parentNode);

	stack<ResourceNode *> groups;
	groups.push(root);

	while (!groups.empty())
	{
		ResourceNode *current = groups.top();
		groups.pop();
		
		YAML::Node currentParent = parents.top();
		parents.pop();

		YAML::Node node;
		node["name"] = current->name();
		node["node"] = static_cast<int>(current->nodeType());

		if (current->nodeType() == ResourceNode::NodeType::Handle)
		{
			ResourceHandle *handle = dynamic_cast<ResourceHandle *>(current);
			node["type"] = handle->type();
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

	std::string outPath = meta;
	std::ofstream fout(outPath);
	fout << rootNode;

	return true;
}
