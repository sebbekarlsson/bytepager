cmake_minimum_required(VERSION 3.20)

project(bytepager_test)

file(GLOB PUBLIC_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB bytepager_test_sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

add_executable(bytepager_test ${bytepager_test_sources})

set(BYTEPAGER_TEST_COMPILE_FLAGS -g -Wall)
target_compile_options(bytepager_test PUBLIC ${BYTEPAGER_TEST_COMPILE_FLAGS})
target_link_libraries(bytepager_test PUBLIC bytepager_static)
