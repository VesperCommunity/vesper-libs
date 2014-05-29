
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

# add compiler flags to define C version
# and to compile position independent code
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c89")

# add compiler flags to enable strict compilation in debug mode
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0 --coverage")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -Wextra -pedantic")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wmissing-prototypes")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wstrict-prototypes")

# compile sources into executable
add_executable(vesper-test ${HEADERS} ${SOURCES})

# add external libraries linked to shared module library
target_link_libraries(vesper-test vesper-sphtp)

# add rule to install executable
install(TARGETS vesper-test RUNTIME DESTINATION bin)
