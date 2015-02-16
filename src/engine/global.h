#ifndef GLOBAL_H
#define GLOBAL_H

#if defined(_WIN32) || !defined(__CYGWIN__) //Windows platform (not Posix sygwin)
    #define PLATFORM_WINDOWS
    #define PLATFORM_STR "windows"
#elif defined(__APPLE__) && defined(__MACH__) //Apple platform (Mac or iOS)
    #include <TargetConditionals.h>
    #if defined(TARGET_OS_MAC)
        #define PLATFORM_MAC
        #define PLATFORM_STR "mac"
    #elif defined(TARGET_OS_IPHONE)
        #define PLATFORM_IOS
        #define PLATFORM_STR "ios"
    #endif
#elif defined(__linux__) //Linux kernel
    #if defined(__ANDROID__) //Android
        #define PLATFORM_ANDROID
        #define PLATFORM_STR "android"
    #else //Other Linux-like
        #define PLATFORM_LINUX
        #define PLATFORM_STR "linux"
    #endif
#else
    #error Platform not defined!
#endif

#if defined(PLATFORM_WINDOWS)
    #if defined(__GNUC__) //GCC on Windows
        #define DECL_EXPORT __attribute__ ((dllexport))
        #define DECL_IMPORT __attribute__ ((dllimport))
    #elif defined(_MSC_VER) //Visual Studio
        #define DECL_EXPORT __declspec(dllexport)
        #define DECL_IMPORT __declspec(dllimport)
    #else //Other compiler
        #define DECL_EXPORT
        #define DECL_IMPORT
    #endif
#else
    #if __GNUC__ >= 4 //GNU GCC
        #define DECL_EXPORT __attribute__ ((visibility ("default")))
        #define DECL_IMPORT
    #else //Other
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