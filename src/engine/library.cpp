#include "library.h"

#if defined(_WIN32)
#include <Windows.h>
#define LIBRARY_EXT ".dll"
typedef HMODULE lhandle;
#elif defined(__linux__)
#include <dlfcn.h>
typedef void* lhandle;
#define LIBRARY_EXT ".so"
#endif

static const int extSize = sizeof(LIBRARY_EXT) - 1;

Library::Library()
	: _name(),
	_handle(nullptr)
{
}

Library::Library(const std::string& name)
	: _name(name),
	_handle(nullptr)
{
}

Library::~Library()
{
	unload();
}

std::string Library::name() const
{
	return _name;
}

void Library::setName(const std::string& name)
{
	_name = name;
}

bool Library::load()
{
	if (_name.substr(_name.size() - extSize, extSize) != LIBRARY_EXT)
		_name.append(LIBRARY_EXT);

#if defined(_WIN32)
	_handle = (void*)LoadLibraryA(_name.c_str());
	return _handle != nullptr;
#elif defined(__linux__)
	_handle = dlopen(_name.c_str(), RTLD_LAZY);
	return _handle != nullptr;
#endif
}

bool Library::unload()
{
	lhandle handle = nullptr;
#if defined(_WIN32)
	handle = (lhandle)_handle;
	return FreeLibrary(handle) == TRUE;
#elif defined(__linux__)
	handle = _handle;
	return dlclose(_handle);
#endif
}

FunctionPointer Library::resolve(const char *symbol) const
{
#if defined(_WIN32)
	return (FunctionPointer)GetProcAddress((lhandle)_handle, symbol);
#elif defined(__linux__)
	return (FunctionPointer)dlsym(_handle, symbol);
#endif
}
