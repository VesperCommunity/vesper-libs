
project(vesper-libs)
cmake_minimum_required(VERSION 2.8)

# enable documentation generation
FIND_PACKAGE(Doxygen)
if (DOXYGEN_FOUND)
    configure_file(Doxyfile.in ${PROJECT_BINARY_DIR}/Doxyfile @ONLY IMMEDIATE)
    add_custom_target(docs COMMAND ${DOXYGEN_EXECUTABLE}
        ${PROJECT_BINARY_DIR}/Doxyfile
        SOURCES ${PROJECT_BINARY_DIR}/Doxyfile)
else()
    message(WARNING "Doxygen is needed to build the documentation.")
endif()

# put binary output in bin/ subdirectory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(LIBRARY_OUTPUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# select Release build type as default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()
message(STATUS "'${CMAKE_BUILD_TYPE}' built type was selected.")

# add modules
add_subdirectory(vesper_log)
