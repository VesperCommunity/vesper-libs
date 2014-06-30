
project(vesper-cmcp)
cmake_minimum_required(VERSION 2.8)

# add API header files of this module
set(API_HEADERS
    ${PROJECT_SOURCE_DIR}/vsp_cmcp.h
)

# add header files of this module
set(HEADERS
    # currently no headers
)

# add source files of this module
set(SOURCES
    ${PROJECT_SOURCE_DIR}/vsp_network_connector.c
)

# add object files to be compiled
add_library(vesper-cmcp-objects OBJECT ${API_HEADERS} ${HEADERS} ${SOURCES})

# combine object files to static and shared library
add_library(vesper-cmcp-static STATIC $<TARGET_OBJECTS:vesper-cmcp-objects>)
add_library(vesper-cmcp SHARED $<TARGET_OBJECTS:vesper-cmcp-objects>)

# add external libraries linked to shared module library
target_link_libraries(vesper-cmcp nanomsg vesper-error)

# add rule to install public header file
install(FILES ${API_HEADERS} DESTINATION include)
