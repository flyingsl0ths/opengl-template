list(APPEND STB "${CMAKE_SOURCE_DIR}/ext/stb/stb_image.h" "stb_def.h")

list(APPEND GLAD "glad/glad.h" "glad/glad.c" "glad/khrplatform.h")

list(
  APPEND
  UTILS
  "utils/buffers.hpp"
  "utils/files.hpp"
  "utils/files.cpp"
  "utils/shader.hpp"
  "utils/shader.cpp"
  "utils/shapes.hpp"
  "utils/shapes.cpp")

add_library(glaze STATIC common.hpp ${GLAD} ${STB} ${UTILS})

target_compile_features(glaze PRIVATE cxx_std_17)

target_include_directories(glaze PUBLIC "${CMAKE_SOURCE_DIR}/ext"
                                        "${CMAKE_SOURCE_DIR}/src")

target_link_libraries(glaze PUBLIC compile-options glm glfw)
