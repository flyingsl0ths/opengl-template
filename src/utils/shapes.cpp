#include <optional>

#include "buffers.hpp"
#include "shapes.hpp"

#include <glad/glad.h>

namespace glaze::shapes
{

triangle_t make_triangle(bool const keep_vertices)
{
    using vertex_array_t = std::array<f32, TRIANGLE_VERTEX_DATA_SIZE>;

    constexpr vertex_array_t VERTICES = {
        // clang-format off
        -0.5F, -0.5F, 0.0F, // left  
         0.5F, -0.5F, 0.0F, // right 
         0.0F,  0.5F, 0.0F  // top
        // clang-format on
    };

    u32 triangle_vbo {};

    glGenBuffers(1, &triangle_vbo);

    glBindBuffer(GL_ARRAY_BUFFER, triangle_vbo);

    glBufferData(GL_ARRAY_BUFFER,
                 VERTICES.size() * sizeof(f32),
                 VERTICES.data(),
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    glEnableVertexAttribArray(0);

    return {triangle_vbo,
            3,
            (keep_vertices ? std::optional<vertex_array_t>(VERTICES)
                           : std::optional<vertex_array_t>())};
}

} // namespace utils::shapes
