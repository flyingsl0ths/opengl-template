cmake_minimum_required(VERSION 3.31.6 FATAL_ERROR)

set(NAME "hello-gl")
set(DESCRIPTION "An OpenGL \"hello world\" app")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_DEBUG_POSTFIX "-d")
set(BUILD_SHARED_LIBS OFF)

project(
  ${NAME}
  VERSION 1.0.0
  DESCRIPTION ${DESCRIPTION}
  LANGUAGES CXX C)

option(FETCH_GLFW "Fetch glfw" OFF)
option(FETCH_GLM "Fetch glm" OFF)

add_subdirectory(app)

add_subdirectory(ext)

add_subdirectory(src)

configure_file(${CMAKE_SOURCE_DIR}/run.sh ${CMAKE_SOURCE_DIR}/build/run.sh
               COPYONLY)
