#include "resourcemanager.h"

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
	auto loader = _loaders.find(loader->type());
	if (loader != _loaders.end())
		return;

	auto val = std::make_pair(loader->type(), loader);
	_loaders.insert(val);
}

std::shared_ptr<Resource> ResourceManager::load(const std::string& id)
{
	auto resource = _cache.find(id);
	if (resource != _cache.end())
		return resource->second;

	Resource::Type t = _io->type(id);
}

void ResourceManager::save(const std::string& id, std::shared_ptr<Resource>)
{

}
