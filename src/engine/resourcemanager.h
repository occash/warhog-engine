#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <fstream>

#include "resource.h"

class ENGINE_EXPORT ResourceManager
{
public:
    template<class R>
    static void add();

    template<class T>
    static std::shared_ptr<T> load(const std::string& id);

    template<class T>
    static void save(const std::string& id, std::shared_ptr<T>);

    static std::string base;

private:
    template<class T>
    static Resource<T> *findLoader();

private:
    typedef std::map<BaseResource::ResourceType, std::shared_ptr<BaseResource> > ResourceMap;
    static ResourceMap _loaders;
};

template<class T>
Resource<T> *ResourceManager::findLoader()
{
    auto loaderIter = _loaders.find(Resource<T>::type());
    if (loaderIter == _loaders.end())
        return nullptr;

    auto baseLoader = loaderIter->second;
    Resource<T> *loader = dynamic_cast<Resource<T> *>(baseLoader.get());

    return loader;
}

template<class R>
void ResourceManager::add()
{
    //Check if already exists
    auto loader = _loaders.find(R::type());
    if (loader != _loaders.end())
        return;

    auto val = std::make_pair(R::type(), std::shared_ptr<BaseResource>(new R()));
    _loaders.insert(val);
}

template<class T>
std::shared_ptr<T> ResourceManager::load(const std::string& id)
{
    Resource<T> *loader = findLoader<T>();
    if (nullptr == loader)
        return std::shared_ptr<T>();

    std::ifstream file(base + id, std::ios::binary);
    if (file)
        return loader->load(file);

    return std::shared_ptr<T>();
}

template<class T>
void ResourceManager::save(const std::string& id, std::shared_ptr<T> res)
{
    Resource<T> *loader = findLoader<T>();
    if (nullptr == loader)
        return;

    std::ofstream file(base + id, std::ios::binary);
    if (file)
        loader->save(file, res);
}

#endif
