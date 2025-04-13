include("${CMAKE_SOURCE_DIR}/cmake/git.cmake")

find_package(Git REQUIRED)

set(submodules_to_update "ext/forest" "ext/stb")

if(FETCH_GLM)
  list(APPEND submodules_to_update "ext/glm")
endif()

if(FETCH_GLFW)
  list(APPEND submodules_to_update "ext/glfw")
endif()

message(
  STATUS "Fetching dependencies: glfw=${FETCH_GLFW}, glm=${FETCH_GLM} forest")

git_update_submodules(${submodules_to_update})

if(FETCH_GLFW)
  message(STATUS "[${PROJECT_NAME}]: Fetched glfw")
  add_subdirectory("ext/glfw")
else()
  message(STATUS "[${PROJECT_NAME}]: Found glfw")
  find_package(glfw3 REQUIRED)
endif()

set(GLM_ENABLE_CXX_20 ON)
if(FETCH_GLM)
  message(STATUS "[${PROJECT_NAME}]: Fetched glm")
  add_subdirectory("ext/glm")
else()
  message(STATUS "[${PROJECT_NAME}]: Found glm")
  find_package(glm REQUIRED)
endif()

message(STATUS "[${PROJECT_NAME}]: Adding forest")
add_subdirectory("${CMAKE_SOURCE_DIR}/ext/forest")

set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/ext")
message(STATUS "[${PROJECT_NAME}]: Adding stb")
list(APPEND stb_sources "${SOURCE_DIR}/stb/stb_image.h"
     "${SOURCE_DIR}/stb_def.h")

message(STATUS "[${PROJECT_NAME}]: Adding glad")
list(APPEND glad_sources "${SOURCE_DIR}/glad/glad.c"
     "${SOURCE_DIR}/glad/glad.h" "${SOURCE_DIR}/glad/khrplatform.h")

target_sources(${PROJECT_NAME} PRIVATE ${stb_sources} ${glad_sources})
target_link_libraries(${PROJECT_NAME} PRIVATE forest::forest glfw glm)
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE "${SOURCE_DIR}")
