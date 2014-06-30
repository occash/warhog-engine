#ifndef RESOURCE_H
#define RESOURCE_H

#include <cstdint>
#include <memory>

#include "global.h"

class ENGINE_EXPORT Resource
{
public:
	typedef std::uint64_t Type;
	virtual Type type() const = 0;

protected:
    static Type typeCounter;

    /*virtual bool loadData(std::istream& in, void **data) = 0;
    virtual bool saveData(std::ostream& out, const void *data) = 0;*/
};

template<typename T>
class BaseResource : public Resource
{
public:
	static Type staticType()
	{
		static Type t = typeCounter++;
		return t;
	}

	Type type() const override
	{
		return staticType();
	}

    /*std::shared_ptr<T> load(std::istream&);
    void save(std::ostream&, std::shared_ptr<T>);*/
};

class ResourceLoader
{
public:
	virtual Resource::Type type() const = 0;

	virtual bool load(std::istream& in, Resource *resource) const = 0;
	virtual bool save(std::ostream& out, Resource *resource) const = 0;
};

template<typename R>
class BaseLoader : public ResourceLoader
{
public:
	Resource::Type type() const override
	{
		return R::staticType();
	}
};

/*template<class T>
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
}*/

#endif
