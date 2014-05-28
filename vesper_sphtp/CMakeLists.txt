
project(vesper-sphtp)
cmake_minimum_required(VERSION 2.8)

# add API header files of this module
set(API_HEADERS
    ${PROJECT_SOURCE_DIR}/sphtp.h
)

# add header files of this module
set(HEADERS
    ${PROJECT_SOURCE_DIR}/network_connector.h
)

# add source files of this module
set(SOURCES
    ${PROJECT_SOURCE_DIR}/network_connector.c
)

# add definitions used by the sources
# the SPHTP_BUILD_API flag activates API function export
add_definitions("-DSPHTP_BUILD_API")

# set linker options to hide internal symbols
set(CMAKE_SHARED_LINKER_FLAGS
    "${CMAKE_SHARED_LINKER_FLAGS} -fvisibility=hidden")

# add object files to be compiled
add_library(vesper-sphtp-objects OBJECT ${API_HEADERS} ${HEADERS} ${SOURCES})

# combine object files to static and shared library
add_library(vesper-sphtp-static STATIC $<TARGET_OBJECTS:vesper-sphtp-objects>)
add_library(vesper-sphtp SHARED $<TARGET_OBJECTS:vesper-sphtp-objects>)

# add external libraries linked to shared module library
target_link_libraries(vesper-sphtp)

# add rule to install public header file
install(FILES ${API_HEADERS} DESTINATION include)
