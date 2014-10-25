#ifndef CONFIG_H
#define CONFIG_H

#if defined(_M_IX86) || defined(__i386__)
#define PLATFORM_X86
#endif

#if defined(_M_X64) || defined(__x86_64__)
#define PLATFORM_x64
#endif

#if defined(_M_ARM) || defined(__arm__)
#define PLATFORM_ARM
#endif

#if defined(_M_IA64) || defined(__ia64__)
#define PLATFROM_ITANIUM
#endif

#if defined(_M_PPC) || defined(__powerpc__)
#define PLATFORM_POWERPC
#endif

#define USE_SCALAR

#if defined(PLATFORM_X86) || defined(PLATFORM_x64) || defined(PLATFROM_ITANIUM)
#define USE_SSE
#endif

#if defined(PLATFORM_ARM)
#define USE_NEON
#endif

#if defined(PLATFORM_POWERPC)
#define USE_ALTIVEC
#endif

#if defined(USE_SSE) || defined(USE_NEON) || defined(USE_ALTIVEC)
#undef USE_SCALAR
#endif

#if defined(_MSC_VER)
#define ALIGNED(NAME, SIZE) __declspec(align(SIZE)) NAME
#elif defined(__GNUC__)
#define ALIGNED(NAME, SIZE) NAME __attribute__ ((aligned(SIZE)))
#endif

#endif