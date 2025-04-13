#include "shapes.hpp"
#include "buffers.hpp"

#include <glad/glad.h>

namespace glaze::shapes {

triangle_t make_triangle() {
	using vertex_array_t = std::array<f32, TRIANGLE_VERTEX_DATA_SIZE>;

	constexpr vertex_array_t VERTICES = {
		// clang-format off
        -0.5F, -0.5F, 0.0F, // left  
         0.5F, -0.5F, 0.0F, // right 
         0.0F,  0.5F, 0.0F  // top
		// clang-format on
	};

	u32 triangle_vbo = buffers::make_vbos<1>();

	glBindBuffer(GL_ARRAY_BUFFER, triangle_vbo);

	glBufferData(GL_ARRAY_BUFFER, VERTICES.size() * sizeof(f32),
				 VERTICES.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

	glEnableVertexAttribArray(0);

	return triangle_vbo;
}

square_t make_textured_square(std::array<f32, 32> const data) {
	using index_array_t = std::array<u32, 6>;

	constexpr index_array_t INDICES = {
		// clang-format off
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
		// clang-format on
	};

	auto const [vbo, ebo] = buffers::make_vbos<2>();

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(f32), data.data(),
				 GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, INDICES.size() * sizeof(u32),
				 INDICES.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return {vbo, ebo};
}

cube_t make_cube() {
	constexpr std::array<f32, 180> VERTICES = {
		// clang-format off
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		// clang-format on
	};

	u32 const vbo = buffers::make_vbos<1>();

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, VERTICES.size() * sizeof(f32),
				 VERTICES.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return vbo;
}

} // namespace glaze::shapes
