cmake_minimum_required(VERSION 3.20)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

project(bytepager)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL ${CMAKE_CURRENT_SOURCE_DIR}/)
set(COMMANDS_FILE ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json)

if (EXISTS ${COMMANDS_FILE})
  file(COPY ${COMMANDS_FILE} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/)
endif()

file(GLOB source_files ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

add_executable(bytepager_e ${source_files})
add_library(bytepager_shared SHARED ${source_files})
add_library(bytepager_static STATIC ${source_files})

# set(BYTEPAGER_COMPILE_FLAGS -g -Wall)
set(BYTEPAGER_COMPILE_FLAGS )
target_compile_options(bytepager_e PUBLIC ${BYTEPAGER_COMPILE_FLAGS})
target_compile_options(bytepager_shared PUBLIC ${BYTEPAGER_COMPILE_FLAGS})
target_compile_options(bytepager_static PUBLIC ${BYTEPAGER_COMPILE_FLAGS})

include(bytepager_deps)

bytepager_init_deps(bytepager_e)
bytepager_init_deps(bytepager_shared)
bytepager_init_deps(bytepager_static)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(
  bytepager_e
  PUBLIC
  $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  ${CMAKE_CURRENT_BINARY_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include)


target_include_directories(
  bytepager_shared
  PUBLIC
  $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  ${CMAKE_CURRENT_BINARY_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include)



target_include_directories(
  bytepager_static
  PUBLIC
  $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  ${CMAKE_CURRENT_BINARY_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/include)


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
