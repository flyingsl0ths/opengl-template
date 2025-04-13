#include "app.hpp"

#include <common.hpp>
#include <glaze/buffers.hpp>
#include <glaze/files.hpp>
#include <glaze/shader.hpp>
#include <glaze/shapes.hpp>
#include <glaze/textures.hpp>

#include <concepts>
#include <iostream>
#include <stdexcept>

#include <forest/forest.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace {
inline std::string red_text(str text) {
	return std::string("<rgb=500><b>") + text.data();
}

void on_shader_program_compilation_failed(
	glaze::shader::shader_program_id_t const shader_program,
	std::same_as<glaze::shader::shader_id_t> auto... shader_ids) {

	using namespace glaze;

	auto const mk_logger = [](str error_message) {
		return [error_message](shader::shader_log_t<1024UL> log) -> void {
			forest::print_to(stderr, red_text(error_message));
			forest::print_to(stderr, red_text(log.data()));
			std::cerr << '\n';
		};
	};

	shader::with_shader_log_file<true>(
		shader_program, mk_logger("Failed to compile shader program!\n"));

	auto const log_shader_error = mk_logger("Failed to compile shader!\n");

	glDeleteProgram(shader_program);

	((shader::with_shader_log_file(shader_ids, log_shader_error),
	  glDeleteShader(shader_ids)),
	 ...);
}
} // namespace

app_t::app_t(std::span<char* const> argv) noexcept(false) {
	if (argv.size() < 2) {
		forest::print_to(stderr, "Usage: <app-name> <project-root-dir>\n");

		throw std::runtime_error("Need path to data directory!");
	}

	init_window();

	auto const data_directory = std::string(argv[1UL]) + "/data/";

	init_shaders(data_directory);

	init_textures(data_directory);
}
void app_t::run() noexcept(false) {

	auto const process_input = [](GLFWwindow* const window) {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, 1);
		}
	};

	while (glfwWindowShouldClose(m_window) == 0) {
		process_input(m_window);

		glClearColor(0.0F, 0.0F, 0.0F, 1.0F);

		glClear(GL_COLOR_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_2D,
					  m_texture_ids.light_source_object_texture_id);

		glUseProgram(m_shaders.light_source_shader_program);
		glUseProgram(m_shaders.source_object_shader_program);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(m_window);

		glfwPollEvents();
	}
}

void app_t::init_window() noexcept(false) {
	using namespace glaze;

	if (glfwInit() == GLFW_FALSE) {
		throw std::runtime_error("Failed to initialize GLFW!\n");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	constexpr s32 WINDOW_WIDTH{1280};
	constexpr s32 WINDOW_HEIGHT{720};

	auto* const window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
										  "Hello World!!", nullptr, nullptr);

	if (window == nullptr) {
		glfwTerminate();
		throw std::runtime_error("Failed to initialize the window\n");
	}

	glfwMakeContextCurrent(window);

	auto const update_frame_buffer_size =
		[](GLFWwindow* /*unused*/, s32 const width, s32 const height) {
			// Ensure the viewport matches the new
			// window dimensions; note that width and
			// height will be significantly larger
			// than specified on retina displays.
			glViewport(0, 0, width, height);
		};

	glfwSetFramebufferSizeCallback(window, update_frame_buffer_size);

	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0) {
		throw std::runtime_error("Failed to initialize GLAD!\n");
	}

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	glEnable(GL_DEPTH_TEST);
}

void app_t::init_shaders(std::string const& data_directory) noexcept(false) {
	using namespace glaze;
	auto const vert = shader::make_shader(
		files::read_file(data_directory + "shader/square.vert"),
		GL_VERTEX_SHADER);

	auto const frag = shader::make_shader(
		files::read_file(data_directory + "shader/square.frag"),
		GL_VERTEX_SHADER);

	auto [shader_program, failure] =
		shader::make_shader_program(false, vert.first, frag.first);

	if (failure != shader::shader_compile_status_t::success) {
		on_shader_program_compilation_failed(shader_program, vert.first,
											 frag.first);
		throw std::runtime_error("Failed to create shader(s)!\n");
	}

	glUseProgram(shader_program);
}

void app_t::init_buffers() noexcept(true) {
	u32 cube_vao{};
	glGenVertexArrays(1, &cube_vao);
	glBindVertexArray(cube_vao);

	auto const cube_vbo = glaze::shapes::make_cube();

	glBindBuffer(GL_ARRAY_BUFFER, cube_vbo);

	constexpr usize STRIDE{5 * sizeof(f32)};

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE, (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, STRIDE,
						  (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	m_buffers.m_source_object_vao = cube_vao;
	m_buffers.m_source_object_vbo = cube_vbo;

	u32 light_cube_vao{};
	glGenVertexArrays(1, &light_cube_vao);
	glBindVertexArray(cube_vao);

	auto const light_cube_vbo = glaze::shapes::make_cube();

	glBindBuffer(GL_ARRAY_BUFFER, light_cube_vbo);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE, (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, STRIDE,
						  (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	m_buffers.m_light_source_vao = cube_vao;
	m_buffers.m_light_source_vao = cube_vbo;
}

void app_t::init_textures(std::string const& _) noexcept(false) {}

app_t::~app_t() noexcept(true) {
	if (m_buffers.can_delete_buffers()) {
		glDeleteVertexArrays(1, &m_buffers.m_light_source_vao);
		glDeleteVertexArrays(1, &m_buffers.m_source_object_vao);

		glDeleteBuffers(1, &m_buffers.m_light_source_vbo);
		glDeleteBuffers(1, &m_buffers.m_source_object_vbo);
	}

	if (m_texture_ids.can_delete_textures()) {
		glDeleteTextures(1, &m_texture_ids.light_source_object_texture_id);
		glDeleteTextures(1, &m_texture_ids.source_object_texture_id);
	}

	if (m_shaders.can_delete_shaders()) {
		glDeleteProgram(m_shaders.light_source_shader_program);
		glDeleteProgram(m_shaders.source_object_shader_program);
	}

	glfwDestroyWindow(m_window);

	glfwTerminate();
}
