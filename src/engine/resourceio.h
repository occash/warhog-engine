#ifndef RESOURCEIO_H
#define RESOURCEIO_H

#include "global.h"
#include "resource.h"

#include <memory>

class ResourceNode;

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
	ResourceIO();
	~ResourceIO();

	std::string basePath() const;
	bool setBasePath(const std::string& path);

	/*! Defines if model is read only
		You should provide pack() funcion to create read-only bundle.
	*/
	virtual bool readOnly() const = 0;

	virtual bool createTree(const std::string& path, ResourceNode *& root) = 0;
	virtual bool removeTree(ResourceNode *root) = 0;

	//! Return root resource group
	virtual ResourceNode *rootNode() const;
	virtual bool createGroup(ResourceNode *baseNode, const std::string& id) = 0;
	virtual bool createHandle(ResourceNode *baseNode, BaseResource::Type type, const std::string& id) = 0;
	virtual bool removeNode(ResourceNode *baseNode) = 0;

	virtual bool read(ResourceNode *node, std::shared_ptr<BaseResource> loader, Object *&object) = 0;
	virtual bool write(ResourceNode *node, std::shared_ptr<BaseResource> loader, Object *object) = 0;

private:
	std::string _basePath;
	ResourceNode *_rootNode;

};

#endif