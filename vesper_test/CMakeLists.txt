
project(vesper-test)
cmake_minimum_required(VERSION 2.8)

# add header files of this module
set(HEADERS
    ${PROJECT_SOURCE_DIR}/minunit.h
)

# add source files of this module
set(SOURCES
    ${PROJECT_SOURCE_DIR}/vsp_test.c
)

# compile sources into executable
add_executable(vesper-test ${HEADERS} ${SOURCES})

# add external libraries linked to shared module library
target_link_libraries(vesper-test vesper-error vesper-cmcp)

# add rule to install executable
install(TARGETS vesper-test RUNTIME DESTINATION bin)
