list(APPEND STB "${CMAKE_SOURCE_DIR}/ext/stb/stb_image.h" "stb_def.h")

list(APPEND GLAD "glad/glad.c" "glad/glad.h" "glad/khrplatform.h")

list(
  APPEND
  GLAZE
  "glaze/buffers.hpp"
  "glaze/files.cpp"
  "glaze/files.hpp"
  "glaze/shader.cpp"
  "glaze/shader.hpp"
  "glaze/shapes.cpp"
  "glaze/shapes.hpp"
  "glaze/time.hpp")

add_library(glaze STATIC common.hpp ${GLAD} ${STB} ${GLAZE})

target_compile_features(glaze PRIVATE cxx_std_17)

target_include_directories(glaze PUBLIC "${CMAKE_SOURCE_DIR}/ext"
                                        "${CMAKE_SOURCE_DIR}/src")

target_link_libraries(glaze PUBLIC compile-options glm glfw)
