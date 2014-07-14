#include "resourcemanager.h"
#include "resourceio.h"
#include "resourcegroup.h"

#include <list>
#include <string>
#include <sstream>
#include <algorithm>

std::list<std::string> split(const std::string &s, char delim)
{
	std::list<std::string> elems;
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) 
	{
		elems.push_back(item);
	}
	return elems;
}

ResourceManager::ResourceManager(std::shared_ptr<ResourceIO> io)
	: _io(io)
{
}

ResourceManager::~ResourceManager()
{
	_io->clear();
}

void ResourceManager::setBasePath(const std::string& path)
{
	_io->setBasePath(path);
}

std::string ResourceManager::basePath() const
{
	return _io->basePath();
}

void ResourceManager::addLoader(std::shared_ptr<BaseResource> loader)
{
	_loaders.insert(std::make_pair(loader->type(), loader));
}

std::shared_ptr<Object> ResourceManager::load(const std::string& id)
{
	//No id provided
	if (id.empty())
		return std::shared_ptr<Object>();

	//Split path to node names
	//Last string interpreted as object id
	std::list<std::string> groupNames = split(id, '/');

	//Fetch groups
	ResourceNode *node = _io->rootNode();
	for (std::string groupName : groupNames)
	{
		node = node->child(groupName);
		if (!node)
			return std::shared_ptr<Object>();
	}

	if (node->nodeType() != ResourceNode::NodeType::Handle)
		return std::shared_ptr<Object>();

	ResourceHandle *handle = dynamic_cast<ResourceHandle *>(node);
	if (!handle)
		return std::shared_ptr<Object>();

	LoaderMap::iterator loader = _loaders.find(handle->type());
	if (loader == _loaders.end())
		return std::shared_ptr<Object>();

	std::shared_ptr<BaseResource> resource = loader->second;

	Object *object = nullptr;
	bool result = _io->read(node, resource, object);
	if (!result)
		return std::shared_ptr<Object>();

	return std::shared_ptr<Object>(object);
}

bool ResourceManager::save(const std::string& id, std::shared_ptr<Object> object)
{
	//No id provided
	if (id.empty())
		return false;

	//Split path to node names
	//Last string interpreted as object id
	std::list<std::string> groupNames = split(id, '/');

	//Fetch groups
	ResourceNode *node = _io->rootNode();
	for (std::string groupName : groupNames)
	{
		node = node->child(groupName);
		if (!node)
			return false;
	}

	if (node->nodeType() != ResourceNode::NodeType::Handle)
		return false;

	ResourceHandle *handle = dynamic_cast<ResourceHandle *>(node);
	if (!handle)
		return false;

	LoaderMap::iterator loader = _loaders.find(handle->type());
	if (loader == _loaders.end())
		return false;

	std::shared_ptr<BaseResource> resource = loader->second;
	return _io->write(node, resource, object.get());
}

/*const ResourceGroup *ResourceManager::group(const std::string& id) const
{
	std::list<std::string> groupNames = split(id, '/');

	ResourceGroup *group = _io->rootGroup();
	for (std::string groupName : groupNames)
	{
		group = group->group(groupName);
		if (!group)
			break;
	}

	return group;
}*/

const ResourceNode *ResourceManager::root() const
{
	return _io->rootNode();
}

bool ResourceManager::createGroup(const std::string& id)
{
	if (_io->readOnly())
		return false;

	std::list<std::string> groupNames = split(id, '/');
	auto idIter = --groupNames.end();
	std::string newGroupId = *idIter;
	groupNames.erase(idIter);

	ResourceNode *node = _io->rootNode();
	for (std::string groupName : groupNames)
	{
		node = node->child(groupName);
		if (!node)
			return false;
	}

	return _io->createGroup(node, newGroupId);
}

bool ResourceManager::createHandle(BaseResource::Type type, const std::string& id)
{
	if (_io->readOnly())
		return false;

	std::list<std::string> groupNames = split(id, '/');
	auto idIter = --groupNames.end();
	std::string handleId = *idIter;
	groupNames.erase(idIter);

	ResourceNode *node = _io->rootNode();
	for (std::string groupName : groupNames)
	{
		node = node->child(groupName);
		if (!node)
			return false;
	}

	return _io->createHandle(node, type, handleId);
}

bool ResourceManager::deleteNode(const std::string& id)
{
	if (_io->readOnly())
		return false;

	std::list<std::string> groupNames = split(id, '/');

	ResourceNode *node = _io->rootNode();
	for (std::string groupName : groupNames)
	{
		node = node->child(groupName);
		if (!node)
			return false;
	}

	return _io->removeNode(node);
}
