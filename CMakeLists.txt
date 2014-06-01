
project(vesper-libs)
cmake_minimum_required(VERSION 2.8)

# put binary output in bin/ subdirectory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(LIBRARY_OUTPUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# select Release build type as default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()
message(STATUS "'${CMAKE_BUILD_TYPE}' built type was selected.")

# add include directories
include_directories(SYSTEM "${PROJECT_SOURCE_DIR}")

# add definitions used by the sources
# the VESPER_BUILD_API flag activates API function export
add_definitions("-DVESPER_BUILD_API")

# add compiler flags to define C version
# and to compile position independent code
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c89 -fPIC")

# add compiler flags to enable strict compilation in debug mode
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0 --coverage")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -Wextra -pedantic")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wmissing-prototypes")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wstrict-prototypes")

# set linker options to hide internal symbols
set(CMAKE_SHARED_LINKER_FLAGS
    "${CMAKE_SHARED_LINKER_FLAGS} -fvisibility=hidden")

# add modules
add_subdirectory(vesper_error)
add_subdirectory(vesper_log)
add_subdirectory(vesper_sphtp)
add_subdirectory(vesper_test)
