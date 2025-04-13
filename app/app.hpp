#pragma once

#include <span>
#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

class app_t final {
  public:
	app_t(std::span<char* const> argv) noexcept(false);
	app_t(app_t const&) = delete;
	app_t(app_t&&) = delete;
	app_t& operator=(app_t const&) = delete;
	app_t& operator=(app_t&&) = delete;
	~app_t() noexcept(true);

  public:
	void run() noexcept(false);

  private:
	void init_window() noexcept(false);
	void init_shaders(std::string const& data_directory) noexcept(false);
	void init_buffers() noexcept(true);
	[[maybe_unused]] void
	init_textures(std::string const& data_directory) noexcept(false);

  private:
	struct buffers_t final {
		GLuint m_light_source_vao{GL_INVALID_VALUE};
		GLuint m_source_object_vao{GL_INVALID_VALUE};
		GLuint m_light_source_vbo{GL_INVALID_VALUE};
		GLuint m_source_object_vbo{GL_INVALID_VALUE};

		bool can_delete_buffers() const noexcept(true) {
			return m_light_source_vao != GL_INVALID_VALUE &&
				   m_source_object_vao != GL_INVALID_VALUE &&
				   m_light_source_vbo != GL_INVALID_VALUE &&
				   m_source_object_vbo != GL_INVALID_VALUE;
		}
	};

	struct shaders_t final {
		GLuint light_source_shader_program{};
		GLuint source_object_shader_program{};

		bool can_delete_shaders() const noexcept(true) {
			// 0 is an invalid shader program
			return light_source_shader_program != 0 &&
				   source_object_shader_program != 0;
		}
	};

	struct texture_ids_t final {
		GLuint source_object_texture_id{GL_INVALID_VALUE};
		GLuint light_source_object_texture_id{GL_INVALID_VALUE};

		bool can_delete_textures() const noexcept(true) {
			// 0 is an invalid texture id
			return source_object_texture_id != GL_INVALID_VALUE &&
				   light_source_object_texture_id != GL_INVALID_VALUE;
		}
	};

  private:
	GLFWwindow* m_window = nullptr;
	buffers_t m_buffers{};
	texture_ids_t m_texture_ids{};
	shaders_t m_shaders{};
};
