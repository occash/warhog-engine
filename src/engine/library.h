#ifndef LIBRARY_H
#define LIBRARY_H

#include "global.h"
#include <string>

//! A pointer to function that takes no arguments and return void
typedef void(*FunctionPointer)();

class ENGINE_EXPORT Library
{
public:
	Library();
	Library(const std::string& name);
	~Library();

	std::string name() const;
	void setName(const std::string& name);

	bool load();
	bool unload();

	FunctionPointer resolve(const char *symbol) const;

	DOC_PROP(std::string name)

private:
	std::string _name;
	void *_handle;

};

#endif //LIBRARY_H
