#include "resourceio.h"

ResourceIO::ResourceIO() :
	_basePath(),
	_rootNode(nullptr)
{
}

ResourceIO::~ResourceIO()
{
	if (_rootNode)
		removeTree(_rootNode);
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
		return createTree(path, _rootNode);

	return false;
}

ResourceNode *ResourceIO::rootNode() const
{
	return _rootNode;
}
