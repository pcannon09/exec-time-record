cmake_minimum_required(VERSION 3.18)

file(READ ".private/project.json" projectInfo)

#Set priority variables
string(JSON projectVersion GET "${projectInfo}" version)
string(JSON projectVersionState GET "${projectInfo}" versionState)
string(JSON projectName GET "${projectInfo}" CMakeName)

set(VERSION "${projectVersion} ${projectVersionState}")

project(${projectName}
    VERSION ${projectVersion}
)

# Flags
set(programFlags            "-g -fsanitize=address -Wunused -Wall -Wno-range-loop-analysis")
set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} ${programFlags}")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${programFlags}")

# Warn about the current CXX compiling using for compilation
message(STATUS "CXX Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "${projectName} version: ${projectVersion}")

# Setup
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11) # Minimum version can be C++11 but there is some support for C++98

# Dir setup
set(srcDir "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(testDir "${CMAKE_CURRENT_SOURCE_DIR}/test")
set(incDir "${CMAKE_CURRENT_SOURCE_DIR}/inc")

# Headers from the `inc/` dir
set(headers
    ${incDir}/Stopwatch.hpp
    ${incDir}/Timer.hpp
    ${incDir}/Time.hpp
    ${incDir}/macros.hpp
    ${testDir}/inc/tests.hpp
)

# Sources from the `src/` dir
set(sources
    ${testDir}/src/main.cpp
    ${testDir}/src/stopwatch.cpp
    ${testDir}/src/timer.cpp
    ${testDir}/src/time.cpp
    ${testDir}/src/sleep.cpp
    ${srcDir}/Stopwatch.cpp
    ${srcDir}/Timer.cpp
    ${srcDir}/Time.cpp
    ${srcDir}/Sleep.cpp
)

# Create the shared library (.so)
add_library(${projectName}_shared SHARED ${sources} ${headers})

# Create the static library (.a)
add_library(${projectName}_static STATIC ${sources} ${headers})

# Link the executable
add_executable(${projectName} ${sources} ${headers})

# Optional: Link static/shared libraries to the executable
target_link_libraries(${projectName} PRIVATE ${projectName}_static)

