#ifndef RESOURCEGROUP_H
#define RESOURCEGROUP_H

#include "resource.h"

#include <list>
#include <string>

class ResourceNode
{
public:
	enum class NodeType : char
	{
		Unknown,
		Group,
		Handle
	};

public:
	virtual NodeType nodeType() const = 0;

	virtual std::string name() const = 0;
	virtual bool valid() const = 0;

	virtual ResourceNode *parent() const = 0;
	virtual int childCount() const = 0;
	virtual ResourceNode *child(int index) const = 0;
	virtual ResourceNode *child(const std::string& id) const = 0;

};

class ResourceHandle : public ResourceNode
{
public:
	NodeType nodeType() const final override 
	{ 
		return ResourceNode::NodeType::Handle;
	}

public:
	virtual BaseResource::Type type() const = 0;

};

class ResourceGroup : public ResourceNode
{
public:
	NodeType nodeType() const final override
	{
		return ResourceNode::NodeType::Group;
	}

public:
	//Groups handling
	//virtual int groupCount() const = 0;
	//virtual std::list<std::string> groupNames() const = 0;
	virtual ResourceGroup *group(const std::string& id) const = 0;

	//Resource handling
	//virtual int resourceCount() const = 0;
	//virtual std::list<std::string> resourceNames() const = 0;
	virtual ResourceHandle *resource(const std::string& id) const = 0;

};

#endif