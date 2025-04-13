#pragma once

#include <glad/glad.h>
#include <string>

namespace glaze::textures {

struct texture_opts_t final {
	decltype(GL_TEXTURE_WRAP_S) wrap_s{GL_TEXTURE_WRAP_S};
	decltype(GL_TEXTURE_WRAP_T) wrap_t{GL_TEXTURE_WRAP_T};
	decltype(GL_TEXTURE_MIN_FILTER) min_filter{GL_TEXTURE_MIN_FILTER};
	decltype(GL_TEXTURE_MAG_FILTER) mag_filter{GL_TEXTURE_MAG_FILTER};
	bool flip_vertically{true};
};

GLuint make_texture(std::string const& path,
					texture_opts_t const opts = {}) noexcept;

} // namespace glaze::textures
