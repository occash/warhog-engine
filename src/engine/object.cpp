#include "object.h"

Object::Object()
{
}

Object::~Object()
{
}

const Api * Object::classApi()
{
	static const Api staticApi("Object", nullptr);
	return &staticApi;
}

const Api * Object::api() const
{
	return Object::classApi();
}
