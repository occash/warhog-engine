#include "resourceio.h"

ResourceIO::ResourceIO(const std::string& basePath) :
	_basePath(basePath)
{
}

ResourceIO::~ResourceIO()
{
}

std::string ResourceIO::basePath() const
{
	return _basePath;
}