
project(vesper-util)
cmake_minimum_required(VERSION 2.8)

# add API header files of this module
set(API_HEADERS
    ${PROJECT_SOURCE_DIR}/vsp_api.h
    ${PROJECT_SOURCE_DIR}/vsp_error.h
    ${PROJECT_SOURCE_DIR}/vsp_util.h
)

# add header files of this module
set(HEADERS
    # currently no headers
)

# add source files of this module
set(SOURCES
    ${PROJECT_SOURCE_DIR}/vsp_error.c
)

# add object files to be compiled
add_library(vesper-util-objects OBJECT ${API_HEADERS} ${HEADERS} ${SOURCES})

# combine object files to static and shared library
add_library(vesper-util-static STATIC $<TARGET_OBJECTS:vesper-util-objects>)
add_library(vesper-util SHARED $<TARGET_OBJECTS:vesper-util-objects>)

# add external libraries linked to shared module library
target_link_libraries(vesper-util nanomsg)

# add rule to install public header files
install(FILES ${API_HEADERS} DESTINATION include)
