#include <iostream>

#include <common.hpp>
#include <glaze/buffers.hpp>
#include <glaze/files.hpp>
#include <glaze/shader.hpp>
#include <glaze/shapes.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <forest/forest.hpp>

std::string red_text(const str content)
{
    return std::string("<rgb=500><b>") + content.data();
}

void on_shader_program_compilation_failed(const std::vector<u32>& failures,
                                          const u32 shader_program)
{
    using namespace glaze;

    constexpr szt SHADER_LOG_SIZE {512UL};

    auto const log_program_errors =
        [](shader::shader_log_t<SHADER_LOG_SIZE> log)
    {
        forest::print_to(stderr,
                         red_text("Failed to compile shader program\n"));
        forest::print_to(stderr, std::string("<rgb=500><b>") + log.data());
        std::cerr << '\n';
    };

    shader::with_shader_log_file<decltype(log_program_errors),
                                 SHADER_LOG_SIZE,
                                 true>(shader_program, log_program_errors);

    auto const log_errors = [](shader::shader_log_t<SHADER_LOG_SIZE> log)
    {
        forest::print_to(stderr, red_text("Failed to compile shader\n"));
        forest::print_to(stderr, red_text(log.data()));
        std::cerr << '\n';
    };

    for (const u32 shader_id : failures)
    {
        shader::with_shader_log_file<decltype(log_errors), SHADER_LOG_SIZE>(
            shader_id, log_errors);

        glDeleteShader(shader_id);
    }

    glDeleteProgram(shader_program);
}

s32 main(const s32 argc, const char* const argv[])
{
    using namespace glaze;

    if (argc < 2)
    {
        forest::print_to(stderr,
                         red_text("Usage: <app-name> <project-root-dir>\n"));
        return -1;
    }

    if (glfwInit() == GLFW_FALSE)
    {
        forest::print_to(stderr, red_text("Failed to initialize GLFW!\n"));
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    constexpr s32 WINDOW_WIDTH {1280};
    constexpr s32 WINDOW_HEIGHT {720};
    auto* const   window = glfwCreateWindow(
        WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World!!", nullptr, nullptr);

    if (window == nullptr)
    {
        forest::print_to(stderr, red_text("Failed to initialize the window\n"));
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    auto const update_frame_buffer_size =
        [](GLFWwindow* /*unused*/, s32 const width, s32 const height)
    {
        // Ensure the viewport matches the new
        // window dimensions; note that width and
        // height will be significantly larger
        // than specified on retina displays.
        glViewport(0, 0, width, height);
    };

    glfwSetFramebufferSizeCallback(window, update_frame_buffer_size);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        forest::print_to(stderr, red_text("Failed to initialize GLAD!\n"));
        return -1;
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    auto const delete_objects = [window](u32 const vao, u32 const vbo)
    {
        glDeleteVertexArrays(1, &vao);

        glDeleteBuffers(1, &vbo);

        glfwDestroyWindow(window);

        glfwTerminate();
    };

    u32 vao {};
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    auto const [triangle_vbo, triangle_vertex_count, _] =
        shapes::make_triangle();

    const std::string data_directory = std::string(argv[1UL]) + "/data/";

    auto vertex_shader = shader::make_shader(
        files::read_file(data_directory + "shader/vertex.vert"),
        GL_VERTEX_SHADER);

    auto fragment_shader = shader::make_shader(
        files::read_file(data_directory + "shader/fragment.frag"),
        GL_FRAGMENT_SHADER);

    if (!vertex_shader && !fragment_shader)
    {
        delete_objects(vao, triangle_vbo);
        return -1;
    }

    auto [shader_program, failures] = shader::make_shader_program(
        std::vector<shader::shader_t> {std::move(vertex_shader.value()),
                                       std::move(fragment_shader.value())});

    vertex_shader.reset();

    fragment_shader.reset();

    if (failures)
    {
        on_shader_program_compilation_failed(*failures, shader_program);

        delete_objects(vao, triangle_vbo);

        return -1;
    }

    auto const process_input = [](GLFWwindow* window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, 1);
        }
    };

    while (glfwWindowShouldClose(window) == 0)
    {
        process_input(window);

        glClearColor(0.0F, 0.0F, 0.0F, 1.0F);

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, triangle_vbo);

        glDrawArrays(GL_TRIANGLES, 0, triangle_vertex_count);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glDeleteProgram(shader_program);
    delete_objects(vao, triangle_vbo);

    return 0;
}
