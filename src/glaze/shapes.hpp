#pragma once
#include <array>
#include <optional>
#include <tuple>

#include <common.hpp>

namespace glaze::shapes
{

constexpr szt TRIANGLE_VERTEX_DATA_SIZE {9UL};

using triangle_t = std::
    tuple<u32, s32, std::optional<std::array<f32, TRIANGLE_VERTEX_DATA_SIZE>>>;

/// @brief Contructs a triangle composed of 3 vertices (9 data elements)
/// with a single vertex attribute, set to the number one
/// (note) this function also binds the GL_ARRAY_BUFFER target to the created
/// VBO
/// @param keep_vertices Indicates whether to include the vertex data alongside
/// the returned value
/// @returns A tuple containing the triangle's VBO id and it's vertex count
triangle_t make_triangle(bool keep_vertices = false);

} // namespace glaze::shapes
