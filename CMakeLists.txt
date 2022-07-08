cmake_minimum_required(VERSION 3.22.3 FATAL_ERROR)

option(FETCH_GLFW "Fetch glfw" OFF)
option(FETCH_GLM "Fetch glm" OFF)

set(CMAKE_CXX_EXTENSIONS OFF)

if("${CMAKE_BUILD_TYPE}" STREQUAL "")
  message(STATUS "Building in debug mode")
  set(CMAKE_BUILD_TYPE Debug)
  message(STATUS "Exporting compile commands")
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "In Source Builds Not Allowed")
endif()

set(NAME "hello-world")
set(DESCRIPTION "An OpenGL \"hello world\" app")

project(
  ${NAME}
  VERSION 1.0.0
  DESCRIPTION ${DESCRIPTION}
  LANGUAGES CXX C)

add_library(compile-options INTERFACE)

if(NOT MSVC)
  target_compile_options(
    compile-options INTERFACE "-Wextra;-Wall;-Werror;-Wunused-local-typedefs")
endif()

include("cmake/git.cmake")

find_package(Git REQUIRED)

message(STATUS "Fetching glfw: ${FETCH_GLFW}")
message(STATUS "Fetching glm: ${FETCH_GLM}")

set(submodules_to_update "ext/forest" "ext/stb")

if(FETCH_GLM)
  list(APPEND submodules_to_update "ext/glm")
endif()

if(FETCH_GLFW)
  list(APPEND submodules_to_update "ext/glfw")
endif()

git_update_submodules(${submodules_to_update})

if(FETCH_GLFW)
  add_subdirectory("ext/glfw")
else()
  find_package(glfw3 REQUIRED)
endif()

if(FETCH_GLM)
  add_subdirectory("ext/glm")
else()
  find_package(glm REQUIRED)
endif()

add_subdirectory("ext/forest")

add_subdirectory(src)

add_subdirectory(app)
