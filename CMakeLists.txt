cmake_minimum_required(VERSION 3.20)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

project(scratchbuff)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL ${CMAKE_CURRENT_SOURCE_DIR}/)
set(COMMANDS_FILE ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json)

if (EXISTS ${COMMANDS_FILE})
  file(COPY ${COMMANDS_FILE} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/)
endif()

file(GLOB source_files ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

add_executable(scratchbuff_e ${source_files})
add_library(scratchbuff_shared SHARED ${source_files})
add_library(scratchbuff_static STATIC ${source_files})

set(SCRATCHBUFF_COMPILE_FLAGS -g -Wall)
target_compile_options(scratchbuff_e PUBLIC ${SCRATCHBUFF_COMPILE_FLAGS})
target_compile_options(scratchbuff_shared PUBLIC ${SCRATCHBUFF_COMPILE_FLAGS})
target_compile_options(scratchbuff_static PUBLIC ${SCRATCHBUFF_COMPILE_FLAGS})

include(scratchbuff_deps)

scratchbuff_init_deps(scratchbuff_e)
scratchbuff_init_deps(scratchbuff_shared)
scratchbuff_init_deps(scratchbuff_static)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(
  scratchbuff_e
  PUBLIC
  $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  ${CMAKE_CURRENT_BINARY_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include)


target_include_directories(
  scratchbuff_shared
  PUBLIC
  $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  ${CMAKE_CURRENT_BINARY_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include)



target_include_directories(
  scratchbuff_static
  PUBLIC
  $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  ${CMAKE_CURRENT_BINARY_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include)


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
