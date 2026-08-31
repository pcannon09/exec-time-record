/**
 * EXAMPLEpredefines.h - pcannonProjectStandards
 * Predefines for C and C++ projects
 * STD Information: 20250723 - 1.0S
 */

#ifndef INCLUDE_C_EXAMPLEPREDEFINES_H_
#define INCLUDE_C_EXAMPLEPREDEFINES_H_

// Project setup
#define EXAMPLE_DEFAULT_C_STD			201112L

// Versioning
#define EXAMPLE_VERSION_MAJOR            0
#define EXAMPLE_VERSION_MINOR            0
#define EXAMPLE_VERSION_PATCH            1

#define EXAMPLE_VERSION_STD              0

// Version states:
// * dev
// * beta
// * build
#define EXAMPLE_VERSION_STATE          "dev"

#define EXAMPLE_VERSION                ((EXAMPLE_VERSION_MAJOR<<16)|(EXAMPLE_VERSION_MINOR<<8)|(EXAMPLE_VERSION_PATCH)|(EXAMPLE_VERSION_STATE << 24))

#define EXAMPLE_VERSION_CHECK(EXAMPLE_VERSION_MAJOR, EXAMPLE_VERSION_MINOR, EXAMPLE_VERSION_PATCH, EXAMPLE_VERSION_STATE) \
    (((EXAMPLE_VERSION_MAJOR)<<16)|((EXAMPLE_VERSION_MINOR)<<8)|(EXAMPLE_VERSION_PATCH)|((EXAMPLE_VERSION_STATE) << 24))

// Macro utils
#define EXAMPLE_STRINGIFY(x) #x
#define EXAMPLE_TOSTRING(x) EXAMPLE_STRINGIFY(x)

#ifndef EXAMPLE_DEV
#   define EXAMPLE_DEV      1
#endif

#if defined(WIN32) || defined(_WIN32)
#	define EXAMPLE_OS_WIN32
#elif defined(__APPLE__) || defined(__MACH__) || defined(Macintosh)
#	define EXAMPLE_OS_MACOS
#elif defined(__linux__)
#	define EXAMPLE_OS_UNIX_LINUX
#elif defined(__unix) || defined(__unix__)
#	define EXAMPLE_OS_UNIX
#elif defined(__FreeBSD__)
#	define EXAMPLE_OS_FREEBSD
#else
#	error "Current platform might not supported"
#endif // defined(WIN32) // Platform check

#endif  // INCLUDE_C_EXAMPLEPREDEFINES_H_

