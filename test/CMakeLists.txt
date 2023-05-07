cmake_minimum_required(VERSION 3.20)

project(scratchbuff_test)

file(GLOB PUBLIC_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB scratchbuff_test_sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

add_executable(scratchbuff_test ${scratchbuff_test_sources})

set(SCRATCHBUFF_TEST_COMPILE_FLAGS -g -Wall)
target_compile_options(scratchbuff_test PUBLIC ${SCRATCHBUFF_TEST_COMPILE_FLAGS})
target_link_libraries(scratchbuff_test PUBLIC scratchbuff_static)
