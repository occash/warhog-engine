#include "resourcemanager.h"
#include "resourceio.h"

#include <string>
#include <sstream>
#include <algorithm>

std::list<std::string> split(const std::string &s, char delim) 
{
	std::list<std::string> elems;
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
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

void ResourceManager::addLoader(std::shared_ptr<ResourceLoader> loader)
{
	//Check if already exists
	auto l = _loaders.find(loader->type());
	if (l != _loaders.end())
		return;

	auto val = std::make_pair(loader->type(), loader);
	_loaders.insert(val);
}

std::shared_ptr<Resource> ResourceManager::load(const std::string& id)
{
	auto resource = _cache.find(id);
	if (resource != _cache.end())
		return resource->second;

	std::list<std::string> groups = split(id, '/');
	tree<ResourceGroup>::pre_order_iterator root = _io->paths.begin();
	for (std::string group : groups)
	{
		_io->paths.begin(root);
	}
}

void ResourceManager::save(const std::string& id, std::shared_ptr<Resource>)
{

}
