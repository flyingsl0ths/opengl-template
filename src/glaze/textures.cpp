#include "textures.hpp"

#include <iostream>

#include <common.hpp>
#include <glaze/buffers.hpp>

#include <stb_def.h>

namespace glaze::textures {

GLuint make_texture(std::string const& path,
					texture_opts_t const opts) noexcept {
	bool had_error{};

	u32 const texture = buffers::make_vbos<1>();

	glBindTexture(GL_TEXTURE_2D, texture);

	auto const [wrap_s, wrap_t, min_filter, mag_filter, flip_vertically] = opts;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);

	// load and generate the texture
	s32 width, height, nrChannels;

	stbi_set_flip_vertically_on_load(flip_vertically);

	unsigned char* data =
		stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
					 GL_UNSIGNED_BYTE, data);

		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cerr << "Failed to load texture" << std::endl;
		had_error = true;
	}

	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, 0);

	return had_error ? GL_INVALID_VALUE : texture;
}

} // namespace glaze::textures
