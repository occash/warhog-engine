#ifndef RESOURCEGROUP_H
#define RESOURCEGROUP_H

#include <string>

class ResourceGroup
{
public:
	virtual ResourceGroup *parent() const = 0;
	virtual ResourceGroup *group(const std::string& id) const = 0;
	//virtual bool create(const std::string& id) = 0;

};

#endif