#ifndef RESOURCEIO_H
#define RESOURCEIO_H

#include "global.h"
#include "resource.h"

#include <memory>

class ResourceGroup;

/*! \breif This class Handle input/output operations of resources
	ResourceIO stores tree-like group structure 
	(You can store it internally as you like).
	It also keep track the types of resources in bundle
	and must provide resource loaders with input and output
	streams.
*/
class ENGINE_EXPORT ResourceIO
{
public:
	ResourceIO(const std::string& basePath);
	~ResourceIO();

	std::string basePath() const;

	/*! Defines if model is read only
		You should provide pack() funcion to create read-only bundle.
	*/
	virtual bool isReadOnly() const = 0;

	//! Return root resource group
	virtual ResourceGroup *rootGroup() const = 0;
	virtual bool createSubGroup(ResourceGroup *baseGroup, const std::string& groupName) = 0;
	virtual bool removeSubGroup(ResourceGroup *baseGroup) = 0;

	virtual bool read(std::shared_ptr<BaseResource> loader, const std::string& id, Object *& object) = 0;
	virtual bool write(std::shared_ptr<BaseResource> loader, const std::string& id, Object *object) = 0;

private:
	std::string _basePath;

};

#endif