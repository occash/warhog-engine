#ifndef RESOURCEGROUP_H
#define RESOURCEGROUP_H

#include <resource.h>

#include <string>

class ResourceGroup
{
public:
	virtual ResourceGroup *parent() const = 0;
	virtual std::string name() const = 0;
	virtual std::list<std::string> groupNames() const = 0;
	virtual ResourceGroup *group(const std::string& id) const = 0;
	virtual std::list<std::string> resourceNames() const;
	virtual BaseResource::Type type(const std::string& name) const = 0;

};

#endif