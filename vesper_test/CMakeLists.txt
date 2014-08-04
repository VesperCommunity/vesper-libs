
project(vesper-test)
cmake_minimum_required(VERSION 2.8)

# add header files of this module
set(HEADERS
    ${PROJECT_SOURCE_DIR}/minunit.h
    ${PROJECT_SOURCE_DIR}/vsp_test.h
)

# add source files of this module
set(SOURCES
    ${PROJECT_SOURCE_DIR}/minunit.c
    ${PROJECT_SOURCE_DIR}/vsp_test.c
    ${PROJECT_SOURCE_DIR}/vsp_test_cmcp_connection.c
    ${PROJECT_SOURCE_DIR}/vsp_test_cmcp_datalist.c
    ${PROJECT_SOURCE_DIR}/vsp_test_cmcp_message.c
)

# compile sources into executable
add_executable(vesper-test ${HEADERS} ${SOURCES})

# add external libraries linked to shared module library
target_link_libraries(vesper-test vesper-util vesper-cmcp)

# add rule to install executable
install(TARGETS vesper-test RUNTIME DESTINATION bin)

# add custom target 'make check' to enable testing
add_custom_target(check COMMAND vesper-test)
