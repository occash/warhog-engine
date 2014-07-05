#ifndef RESOURCE_H
#define RESOURCE_H

#include <cstdint>
#include <memory>

#include "global.h"
#include "object.h"

class BaseResource
{
public:
	typedef std::uint64_t Type;

	virtual Type type() const = 0;
	virtual bool load(std::istream& in, Object *&resource) const = 0;
	virtual bool save(std::ostream& out, Object *resource) const = 0;

protected:
	static Type typeCounter;

};

template<typename T>
class Resource : public BaseResource
{
public:
	static Type staticType()
	{
		const static Type t = ++typeCounter;
		return t;
	}

	Type type() const override
	{
		return staticType();
	}

};

#endif