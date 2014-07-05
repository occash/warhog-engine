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
}

void ResourceManager::addLoader(std::shared_ptr<BaseResource> loader)
{
	_loaders.insert(std::make_pair(loader->type(), loader));
}

std::shared_ptr<Object> ResourceManager::load(const std::string& id, BaseResource::Type type)
{
	//Guess the type
	if (type == 0)
		return std::shared_ptr<Object>();

	LoaderMap::iterator loader = _loaders.find(type);
	if (loader == _loaders.end())
		return false;

	std::shared_ptr<BaseResource> resource = loader->second;
	Object *object;
	bool res = _io->read(resource, id, object);
	if (!res)
		return std::shared_ptr<Object>();

	return std::shared_ptr<Object>(object);
}

bool ResourceManager::save(const std::string& id, std::shared_ptr<Object> object, BaseResource::Type type)
{
	//No id provided
	if (id.empty())
		return false;

	//Split path to group names
	//Last string interpreted as object id
	std::list<std::string> groupNames = split(id, '/');
	auto idIter = --groupNames.end();
	std::string objectId = *idIter;
	groupNames.erase(idIter);

	//Fetch groups
	ResourceGroup *group = _io->rootGroup();
	for (std::string groupName : groupNames)
	{
		group = group->group(groupName);
		if (!group)
			return false;
	}

	LoaderMap::iterator loader = _loaders.find(type);
	if (loader == _loaders.end())
		return false;

	std::shared_ptr<BaseResource> resource = loader->second;
	return _io->write(resource, id, object.get());
}

const ResourceGroup *ResourceManager::group(const std::string& id) const
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
}

const ResourceGroup *ResourceManager::root() const
{
	return group();
}

bool ResourceManager::createGroup(const std::string& id)
{
	if (_io->isReadOnly())
		return false;

	std::list<std::string> groupNames = split(id, '/');
	auto idIter = --groupNames.end();
	std::string newGroupId = *idIter;
	groupNames.erase(idIter);

	ResourceGroup *group = _io->rootGroup();
	for (std::string groupName : groupNames)
	{
		group = group->group(groupName);
		if (!group)
			return false;
	}

	return _io->createSubGroup(group, newGroupId);
}

bool ResourceManager::deleteGroup(const std::string& id)
{
	if (_io->isReadOnly())
		return false;

	std::list<std::string> groupNames = split(id, '/');

	ResourceGroup *group = _io->rootGroup();
	for (std::string groupName : groupNames)
	{
		group = group->group(groupName);
		if (!group)
			break;
	}

	return _io->removeSubGroup(group);
}