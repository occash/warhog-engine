#ifndef OBJECT_H
#define OBJECT_H

#include "global.h"

#include <string>

//base class
class ENGINE_EXPORT Object
{
public:
	Object() {}
	virtual ~Object() {}

public:
	std::string name;

};

#endif