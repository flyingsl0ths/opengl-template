#pragma once

#include <array>
#include <concepts>
#include <string>
#include <type_traits>
#include <utility>

#include <common.hpp>

#include <glad/glad.h>

namespace glaze::shader {

enum class shader_compile_status_t { success, failure, internal_error };

using shader_id_t = GLuint;
using shader_program_id_t = shader_id_t;
using shader_result_t = std::pair<shader_program_id_t, shader_compile_status_t>;

template <usize log_size = 256UL>
using shader_log_t = std::array<char, log_size>;

constexpr u32 SHADER_ERROR{};

template <bool is_shader_program = false, usize const log_size = 1024UL>
void with_shader_log_file(u32 const shader_id, auto action) {
	static_assert(
		std::is_invocable_v<decltype(action), shader_log_t<log_size>>,
		"Expected callable of type: (shader_log_t<log_size> -> void)");

	if (shader_id == SHADER_ERROR) { return; }

	shader_log_t<log_size> log{};

	if constexpr (is_shader_program) {
		glGetProgramInfoLog(shader_id, log_size, nullptr, log.data());
	} else {
		glGetShaderInfoLog(shader_id, log_size, nullptr, log.data());
	}

	action(std::move(log));
}

shader_result_t make_shader(std::string source, GLenum shader_type) noexcept;

bool shader_program_compiled(shader_program_id_t const program_id) noexcept;

shader_result_t
make_shader_program(bool const delete_shaders,
					std::same_as<shader_id_t> auto... shader_ids) noexcept {
	using enum shader_compile_status_t;

	shader_id_t const program_id = glCreateProgram();

	if (program_id == SHADER_ERROR) { return {program_id, internal_error}; }

	(glAttachShader(program_id, shader_ids), ...);

	glLinkProgram(program_id);

	if (!shader_program_compiled(program_id)) { return {program_id, failure}; }

	if (delete_shaders) { (glDeleteShader(shader_ids), ...); }

	return {program_id, success};
}

} // namespace glaze::shader
