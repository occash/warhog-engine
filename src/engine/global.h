#ifndef GLOBAL_H
#define GLOBAL_H

#include <memory>

template <typename T>
using Ptr = std::shared_ptr<T>;

#if defined(_WIN32) || defined(__CYGWIN__)
	#if defined ENGINE_LIB
		#if defined(__GNUC__)
			#define UMOF_EXPORT __attribute__ ((dllexport))
		#elif defined(_MSC_VER)
			#define UMOF_EXPORT __declspec(dllexport)
		#else
			#define UMOF_EXPORT
		#endif
	#else
		#if defined(__GNUC__)
			#define UMOF_EXPORT __attribute__ ((dllimport))
		#elif defined(_MSC_VER)
			#define UMOF_EXPORT __declspec(dllimport)
		#else
			#define  UMOF_EXPORT
		#endif
	#endif
#else
	#if __GNUC__ >= 4
		#define UMOF_EXPORT __attribute__ ((visibility ("default")))
	#else
		#define UMOF_EXPORT
	#endif
#endif


//For documentation purposes
#define DOC_PROP(x)

#endif