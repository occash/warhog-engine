#ifndef LIBRARY_H
#define LIBRARY_H

#include "global.h"
#include <string>

//! A pointer to function that takes no arguments and return void
typedef void(*FunctionPointer)();

/*! \brief The Library class loads shared libraries at runtime
*/
class ENGINE_EXPORT Library
{
public:
	Library();
	Library(const std::string& name);
	~Library();

	std::string name() const;
	void setName(const std::string& name);

	/*! \brief Loads the library
		The function will return true if the library was
		loaded successfully. You should explicitly call
		this method before calling resolve.
	*/
	bool load();

	/*! \brief Unloads the library
		Returns true if library could be unloaded.
		The library will be unloaded automatically on
		destruction.
	*/
	bool unload();

	/*! \brief Returns the address of exported symbol.
		The function will returns 0 if the symbol cannot
		be resolved or if library wasn't loaded.
		The Library can resolve only C functions.
	*/
	FunctionPointer resolve(const char *symbol) const;

	/*! \brief The property holds file name of the library.

		It is better to omit file extension, since engine
		will automatically append the proper suffix.
		
		On some platforms Library will search in system
		specific locations, unless the name is absolute path.

		The getter will return the full path.

		\accessors name(), setName()
	*/
	DOC_PROP(std::string name)

private:
	std::string _name;
	void *_handle;

};

#endif //LIBRARY_H
