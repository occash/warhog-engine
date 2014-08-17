#ifndef GLOBAL_H
#define GLOBAL_H

#include <memory>

template <typename T>
using Ptr = std::shared_ptr<T>;

#ifdef ENGINE_LIB
#define ENGINE_EXPORT _declspec(dllexport)
#else
#define ENGINE_EXPORT _declspec(dllimport)
#endif

#endif