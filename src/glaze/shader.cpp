#include "shader.hpp"

namespace glaze::shader {

shader_result_t make_shader(std::string source, GLenum const type) noexcept {
	using enum shader_compile_status_t;

	if (source.empty()) { return {SHADER_ERROR, internal_error}; }

	auto result = glCreateShader(type);

	if (result == SHADER_ERROR || result == GL_INVALID_ENUM) {
		return {result, internal_error};
	}

	char const* const data{source.c_str()};

	glShaderSource(result, 1, &data, nullptr);

	glCompileShader(result);

	GLint compile_status{};

	glGetShaderiv(result, GL_COMPILE_STATUS, &compile_status);

	return compile_status == GL_TRUE ? std::pair{result, success}
									 : std::pair{result, failure};
}

bool shader_program_compiled(shader_program_id_t const program_id) noexcept {
	GLint compile_status{};
	glGetProgramiv(program_id, GL_LINK_STATUS, &compile_status);
	return compile_status == GL_TRUE;
}

} // namespace glaze::shader
