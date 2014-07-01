#ifndef RESOURCEIO_H
#define RESOURCEIO_H

#include "resource.h"

#include <fstream>
#include <unordered_map>

class ENGINE_EXPORT ResourceGroup
{
public:
	ResourceGroup(ResourceGroup &&other) :
		name(std::move(other.name)),
		types(std::move(other.types))
	{}

	std::string name;
	std::unordered_map<std::string, Resource::Type> types;

};

class ENGINE_EXPORT ResourceIO
{
public:
	virtual std::shared_ptr<std::istream> get(const std::string& id) = 0;
	virtual std::shared_ptr<std::ostream> set(const std::string& id) = 0;

	std::string basePath;
	tree<ResourceGroup> paths;

};

class ENGINE_EXPORT FileResourceIO : public ResourceIO
{
public:
	FileResourceIO(const std::string& config) 
		: configFile(config) 
	{
	}
	~FileResourceIO() {}

	std::shared_ptr<std::istream> get(const std::string& id) override
	{
		std::shared_ptr<std::istream> in =
			std::make_shared<std::ifstream>(basePath + '/' + id, std::ios::in | std::ios::binary);
		return in;
	}

	std::shared_ptr<std::ostream> set(const std::string& id) override
	{
		std::shared_ptr<std::ostream> out =
			std::make_shared<std::ofstream>(basePath + '/' + id, std::ios::out | std::ios::binary);
		return out;
	}

	std::string configFile;

};

#endif