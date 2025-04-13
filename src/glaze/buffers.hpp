#pragma once

#include <array>
#include <type_traits>

#include <common.hpp>

#include <glad/glad.h>

namespace glaze::buffers {

template <GLsizei total>
auto make_vbos()
	-> std::conditional_t<total == 1, GLuint,
						  std::array<GLuint, static_cast<usize>(total)>> {

	if constexpr (total == 1) {
		GLuint vbo{};
		glGenBuffers(1, &vbo);
		return vbo;
	} else {
		std::array<GLuint, static_cast<usize>(total)> vbo{};
		glGenBuffers(total, vbo.data());
		return vbo;
	}
}

template <GLsizei total>
auto make_vaos()
	-> std::conditional_t<total == 1, GLuint,
						  std::array<GLuint, static_cast<usize>(total)>> {

	if constexpr (total == 1) {
		GLuint vao{};
		glGenVertexArrays(1, &vao);
		return vao;
	} else {
		std::array<GLuint, static_cast<usize>(total)> vaos{};
		glGenVertexArrays(total, vaos.data());
		return vaos;
	}
}

} // namespace glaze::buffers
