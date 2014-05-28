
project(vesper-sphtp)
cmake_minimum_required(VERSION 2.8)

# add header files of this module
set(HEADERS
    ${PROJECT_SOURCE_DIR}/network_connector.h
)

# add source files of this module
set(SOURCES
    ${PROJECT_SOURCE_DIR}/network_connector.c
)

# add object files to be compiled
add_library(vesper-sphtp-objects OBJECT ${HEADERS} ${SOURCES})

# combine object files to static and shared library
add_library(vesper-sphtp-static STATIC $<TARGET_OBJECTS:vesper-sphtp-objects>)
add_library(vesper-sphtp SHARED $<TARGET_OBJECTS:vesper-sphtp-objects>)

# add external libraries linked to shared module library
target_link_libraries(vesper-sphtp)
