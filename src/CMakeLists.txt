list(APPEND STB "${CMAKE_SOURCE_DIR}/ext/stb/stb_image.h" "stb_def.h")

list(APPEND GLAD "glad/glad.c" "glad/glad.h" "glad/khrplatform.h")

list(
  APPEND
  UTILS
  "utils/buffers.hpp"
  "utils/files.cpp"
  "utils/files.hpp"
  "utils/shader.cpp"
  "utils/shader.hpp"
  "utils/shapes.cpp"
  "utils/shapes.hpp"
  "utils/time.hpp")

add_library(glaze STATIC common.hpp ${GLAD} ${STB} ${UTILS})

target_compile_features(glaze PRIVATE cxx_std_17)

target_include_directories(glaze PUBLIC "${CMAKE_SOURCE_DIR}/ext"
                                        "${CMAKE_SOURCE_DIR}/src")

target_link_libraries(glaze PUBLIC compile-options glm glfw)
