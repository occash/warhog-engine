#ifndef RESOURCE_H
#define RESOURCE_H

#include <cstdint>
#include <memory>

#include "global.h"

class ENGINE_EXPORT BaseResource
{
public:
    typedef std::uint64_t ResourceType;
    static ResourceType _typeCounter;

    virtual bool loadData(std::istream& in, void **data) = 0;
    virtual bool saveData(std::ostream& out, const void *data) = 0;
};

template<class T>
class Resource : public BaseResource
{
public:
    static ResourceType type();

    std::shared_ptr<T> load(std::istream&);
    void save(std::ostream&, std::shared_ptr<T>);
};

template<class T>
BaseResource::ResourceType Resource<T>::type()
{
    static ResourceType _type = _typeCounter++;

    return _type;
}

template<class T>
std::shared_ptr<T> Resource<T>::load(std::istream& in)
{
    std::shared_ptr<T> resource;
    void *rawData = nullptr;
    if (!loadData(in, &rawData))
        return resource;

    T *data = reinterpret_cast<T *>(rawData);
    resource = std::shared_ptr<T>(data);

    return resource;
}

template<class T>
void Resource<T>::save(std::ostream& out, std::shared_ptr<T> resource)
{
    const void *rawData = 
        reinterpret_cast<const T *>(resource.get());
    
    saveData(out, rawData);
}

#endif
