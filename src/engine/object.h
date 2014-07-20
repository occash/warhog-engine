#ifndef OBJECT_H
#define OBJECT_H

#include "global.h"
#include "api.h"

#include <string>

#define STR(S) #S
#define OBJECT(Class, Super) \
public: \
	static const Api *classApi() \
	{ \
		static const Api staticApi(STR(Class), Super::classApi()); \
		return &staticApi; \
	} \
	virtual const Api *api() const \
	{ \
		return Class::classApi(); \
	} \
private:

//base class
class ENGINE_EXPORT Object
{
public:
	Object();
	virtual ~Object();

	static const Api *classApi();
	virtual const Api *api() const;

};

#endif