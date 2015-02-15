#include "library.h"

#if defined(PLATFORM_WINDOWS)
    #include <Windows.h>
    #define LIBRARY_EXT ".dll"
    typedef HMODULE lhandle;
#elif defined(PLATFORM_LINUX)
    #include <dlfcn.h>
    typedef void *lhandle;
    #define LIBRARY_EXT ".so"
#endif

static const int extSize = sizeof(LIBRARY_EXT) - 1;

/*! \class Library
    \brief The Library class loads shared libraries at runtime

    Use this class to dynamically load shared library.
    Example:
    ~~~~~~~~~~~~~{.cpp}
    Library library;
    library.setName("Qt5Core");
    library.load();
    ~~~~~~~~~~~~~
*/

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

/*! \property std::string Library::name
    \brief The property holds file name of the library.

    It is better to omit file extension, since engine
    will automatically append the proper suffix.

    On some platforms Library will search in system
    specific locations, unless the name is absolute path.

    The getter will return the full path.

    \accessors name(), setName()
*/

std::string Library::name() const
{
    return _name;
}

void Library::setName(const std::string& name)
{
    _name = name;
}

/*! \brief Loads the library

    The function will return true if the library was
    loaded successfully. You should explicitly call
    this method before calling resolve.
*/
bool Library::load()
{
    if (_name.substr(_name.size() - extSize, extSize) != LIBRARY_EXT)
        _name.append(LIBRARY_EXT);

#if defined(PLATFORM_WINDOWS)
    _handle = (void *)LoadLibraryA(_name.c_str());
    return _handle != nullptr;
#elif defined(PLATFORM_LINUX)
    _handle = dlopen(_name.c_str(), RTLD_LAZY);
    return _handle != nullptr;
#endif
}

/*! \brief Unloads the library

    Returns true if library could be unloaded.
    The library will be unloaded automatically on
    destruction.
*/
bool Library::unload()
{
    lhandle handle = nullptr;
#if defined(PLATFORM_WINDOWS)
    handle = (lhandle)_handle;
    return FreeLibrary(handle) == TRUE;
#elif defined(PLATFORM_LINUX)
    handle = _handle;
    return dlclose(_handle);
#endif
}

/*! \brief Returns the address of exported symbol.

    The function will returns 0 if the symbol cannot
    be resolved or if library wasn't loaded.
    The Library can resolve only C functions.
*/
FunctionPointer Library::resolve(const char *symbol) const
{
#if defined(PLATFORM_WINDOWS)
    return (FunctionPointer)GetProcAddress((lhandle)_handle, symbol);
#elif defined(PLATFORM_LINUX)
    return (FunctionPointer)dlsym(_handle, symbol);
#endif
}
