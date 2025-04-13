#pragma once
#include <tuple>

#include <common.hpp>

namespace glaze::shapes {

constexpr usize TRIANGLE_VERTEX_DATA_SIZE{9UL};

using triangle_t = u32;
using square_t = std::tuple<u32, u32>;
using cube_t = u32;

triangle_t make_triangle();

square_t make_textured_square(std::array<f32, 32> const data);

cube_t make_cube();

} // namespace glaze::shapes
