#ifndef GLOBAL_H
#define GLOBAL_H


#if defined(_WIN32) || defined(__CYGWIN__)
	#if defined(__GNUC__)
		#define DECL_EXPORT __attribute__ ((dllexport))
		#define DECL_IMPORT __attribute__ ((dllimport))
	#elif defined(_MSC_VER)
		#define DECL_EXPORT __declspec(dllexport)
		#define DECL_IMPORT __declspec(dllimport)
	#else
		#define DECL_EXPORT
		#define DECL_IMPORT
	#endif
#else
	#if __GNUC__ >= 4
		#define DECL_EXPORT __attribute__ ((visibility ("default")))
		#define DECL_IMPORT
	#else
		#define DECL_EXPORT
		#define DECL_IMPORT
	#endif
#endif

#if defined ENGINE_LIB
	#define ENGINE_EXPORT DECL_EXPORT
#else
	#define ENGINE_EXPORT DECL_IMPORT
#endif

//For documentation purposes
#define DOC_PROP(x)

#endif