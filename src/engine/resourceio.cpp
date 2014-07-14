#include "resourceio.h"

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
	if (_rootNode)
		result = removeTree(_rootNode);

	if (result)
		result &= createTree(path, _rootNode);

	if (result)
		_basePath = path;

	return result;
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
