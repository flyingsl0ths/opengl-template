set(source_dir "${CMAKE_SOURCE_DIR}/src")

list(
  APPEND
  glaze_sources
  "${source_dir}/common.hpp"
  "${source_dir}/glaze/buffers.hpp"
  "${source_dir}/glaze/files.cpp"
  "${source_dir}/glaze/files.hpp"
  "${source_dir}/glaze/shader.cpp"
  "${source_dir}/glaze/shader.hpp"
  "${source_dir}/glaze/shapes.cpp"
  "${source_dir}/glaze/shapes.hpp"
  "${source_dir}/glaze/time.hpp"
  "${source_dir}/glaze/textures.hpp"
  "${source_dir}/glaze/textures.cpp")

target_sources(${PROJECT_NAME} PRIVATE ${glaze_sources})
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/src")
