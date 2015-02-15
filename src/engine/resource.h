#ifndef RESOURCE_H
#define RESOURCE_H

#include <cstdint>
#include <string>

#include "global.h"
#include "meta/object.h"

class BaseResource
{
public:
    typedef std::string Type;

    virtual Type type() const = 0;
    virtual bool load(std::istream& in, Object *&resource) const = 0;
    virtual bool save(std::ostream& out, Object *resource) const = 0;

};

template<typename T>
class Resource : public BaseResource
{
public:
    static Type staticType()
    {
        return T::classApi()->name();
    }

    Type type() const override
    {
        return staticType();
    }

};

#endif