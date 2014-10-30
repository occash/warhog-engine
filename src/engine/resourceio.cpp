#include "resourceio.h"
#include "resourcegroup.h"

ResourceIO::ResourceIO() :
	_basePath(),
	_rootNode(nullptr)
{
}

ResourceIO::~ResourceIO()
{
}

std::string ResourceIO::basePath() const
{
	return _basePath;
}

bool ResourceIO::setBasePath(const std::string& path)
{
	bool result = true;
	if (_rootNode) {
		result = removeTree(_rootNode);
		_rootNode = nullptr;
	}

	if (path.empty())
		return result;

	_basePath = path;

	if (result)
		result &= createTree(path, _rootNode);

	return result;
}

void ResourceIO::addLoader(std::shared_ptr<BaseResource> loader)
{
	_loaders.insert(std::make_pair(loader->type(), loader));
}

void ResourceIO::removeLoader(std::shared_ptr<BaseResource> loader)
{
	auto result = _loaders.find(loader->type());
	if (result != _loaders.end())
		_loaders.erase(result);
}

ResourceNode *ResourceIO::rootNode() const
{
	return _rootNode;
}

void ResourceIO::clear()
{
	if (_rootNode)
		removeTree(_rootNode);
}

bool ResourceIO::load(ResourceNode *node, std::shared_ptr<Object>& object)
{
	if (node->nodeType() != ResourceNode::NodeType::Handle)
		return false;

	ResourceHandle *handle = dynamic_cast<ResourceHandle *>(node);
	if (!handle)
		return false;

	auto result = _loaders.find(handle->type());
	if (result == _loaders.end())
		return false;

	Object *rawObject = nullptr;
	bool readed = read(node, result->second, rawObject);
	if (!readed || !rawObject)
		return false;

	object.reset(rawObject);
	return true;
}

bool ResourceIO::save(ResourceNode *node, std::shared_ptr<Object> object)
{
	if (node->nodeType() != ResourceNode::NodeType::Handle)
		return false;

	ResourceHandle *handle = dynamic_cast<ResourceHandle *>(node);
	if (!handle)
		return false;

	auto result = _loaders.find(handle->type());
	if (result == _loaders.end())
		return false;

	return write(node, result->second, object.get());
}
