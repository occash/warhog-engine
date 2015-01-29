#ifndef RESOURCEIO_H
#define RESOURCEIO_H

#include "global.h"
#include "resource.h"

#include <memory>
#include <map>

class ResourceNode;
class ResourceManager;

/*! \brief This class Handle input/output operations of resources
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

	void addLoader(std::shared_ptr<BaseResource> loader);
	void removeLoader(std::shared_ptr<BaseResource> loader);

	bool load(ResourceNode *node, std::shared_ptr<Object>& object);
	bool save(ResourceNode *node, std::shared_ptr<Object> object);

	/*! Defines if model is read only
		You should provide pack() funcion to create read-only bundle.
	*/
	virtual bool readOnly() const = 0;
	//virtual bool pack(ResourceNode *root, ResourceNode *& newRoot);

	virtual bool createTree(const std::string& path, ResourceNode *& root) = 0;
	virtual bool removeTree(ResourceNode *root) = 0;

	//! Return root resource group
	ResourceNode *rootNode() const;
	virtual ResourceNode *createGroup(ResourceNode *baseNode, const std::string& id) = 0;
	virtual ResourceNode *createHandle(ResourceNode *baseNode, BaseResource::Type type, const std::string& id) = 0;
	virtual bool removeNode(ResourceNode *node) = 0;
	virtual bool renameNode(ResourceNode *node, const std::string& id) = 0;

	virtual bool read(ResourceNode *node, std::shared_ptr<BaseResource> loader, Object *&object) = 0;
	virtual bool write(ResourceNode *node, std::shared_ptr<BaseResource> loader, Object *object) = 0;

protected:
	friend class ResourceManager;

	void clear();

private:
	typedef std::map<BaseResource::Type, std::shared_ptr<BaseResource>> LoaderMap;

	LoaderMap _loaders;
	std::string _basePath;
	ResourceNode *_rootNode;

};

#endif