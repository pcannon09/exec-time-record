/**
 * @file ETRpredefines.h
 * @brief Version macros, string helpers, and platform detection (pcannonProjectStandards).
 *
 * STD Information: 20250723 - 1.0S
 */

#ifndef INCLUDE_C_ETRPREDEFINES_H_
#define INCLUDE_C_ETRPREDEFINES_H_

// Versioning
#define ETR_VERSION_MAJOR            1
#define ETR_VERSION_MINOR            0
#define ETR_VERSION_PATCH            0

#define ETR_VERSION_STD              20260831

// Version states:
// * dev
// * beta
// * build
#define ETR_VERSION_STATE          "build"

#define ETR_VERSION                ((ETR_VERSION_MAJOR<<16)|(ETR_VERSION_MINOR<<8)|(ETR_VERSION_PATCH)|(ETR_VERSION_STATE << 24))

#define ETR_VERSION_CHECK(ETR_VERSION_MAJOR, ETR_VERSION_MINOR, ETR_VERSION_PATCH, ETR_VERSION_STATE) \
    (((ETR_VERSION_MAJOR)<<16)|((ETR_VERSION_MINOR)<<8)|(ETR_VERSION_PATCH)|((ETR_VERSION_STATE) << 24))

// Macro utils
#define ETR_STRINGIFY(x) #x
#define ETR_TOSTRING(x) ETR_STRINGIFY(x)

#ifndef ETR_DEV
#   define ETR_DEV      1
#endif

#if defined(WIN32) || defined(_WIN32)
#	define ETR_OS_WIN32
#elif defined(__APPLE__) || defined(__MACH__) || defined(Macintosh)
#	define ETR_OS_MACOS
#elif defined(__linux__)
#	define ETR_OS_UNIX_LINUX
#elif defined(__unix) || defined(__unix__)
#	define ETR_OS_UNIX
#elif defined(__FreeBSD__)
#	define ETR_OS_FREEBSD
#else
#	error "Current platform might not supported"
#endif // defined(WIN32) // Platform check

#endif  // INCLUDE_C_ETRPREDEFINES_H_

