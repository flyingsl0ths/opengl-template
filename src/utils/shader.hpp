#pragma once

#include <array>
#include <optional>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include <common.hpp>

#include <glad/glad.h>

namespace glaze::shader
{

using shader_t                = std::pair<std::string, GLenum>;
using shader_compile_result_t = std::pair<u32, std::optional<std::vector<u32>>>;

template <szt log_size>
using shader_log_t = std::array<char, log_size>;

constexpr u32 SHADER_ERROR {};

/// @brief Attempts to retreive the log of a valid shader
/// and forwards it to the given callable
/// @param log_size The allowed size of the log
/// @param is_shader_program Used to obtain either a shader/shader program log
/// @param shader_id The shader/shader program id
/// @param T The callable
template <typename T, szt log_size, bool is_shader_program = false>
void with_shader_log_file(u32 const shader_id, T action)
{
    static_assert(
        std::is_invocable_v<T, shader_log_t<log_size>>,
        "Expected callable of type: (shader_log_t<log_size> -> void)");

    if (shader_id == SHADER_ERROR) { return; }

    shader_log_t<log_size> log {};

    if constexpr (is_shader_program)
    {
        glGetProgramInfoLog(shader_id, log_size, nullptr, log.data());
    }
    else { glGetShaderInfoLog(shader_id, log_size, nullptr, log.data()); }

    action(std::move(log));
}

/// @brief Attempts to create a shader_t instance from the given input
/// by checking if the source is not empty and the type is a valid GLenum
/// @param source The shader's source code
/// @param type The shader's type
/// @returns A valid shader_t instance or nothing
std::optional<shader_t> make_shader(std::string source, GLenum type) noexcept;

/// @brief Checks if a valid shader was successfully
/// compiled by checking if it's id and the value of it's
/// GL_COMPILE_STATUS attribute are not equal to utils::shader::SHADER_ERROR
/// @returns true if the shader compiled successfully and false otherwise
bool shader_compiled(u32 shader_id) noexcept;

/// @brief Checks if a valid shader program was successfully
/// compiled by checking if it's id and the value of it's
/// GL_LINK_STATUS attribute are not equal to utils::shader::SHADER_ERROR
/// @returns true if the shader compiled successfully and false otherwise
bool shader_program_compiled(u32 shader_program_id) noexcept;

/// @brief Attempts to delete a shader program and it's linked shaders.
/// This function assumes all given shader id's (including the shader program
/// id) are valid and associated with the shader program and as a result it
/// performs no checks to ensure valid id's
/// @param shader_program_id The id of the shader program to delete
/// @param shader_ids The id's of the shaders associated with the shader program
void delete_shader_program(u32               shader_program_id,
                           std::vector<u32>& shader_ids) noexcept;

/// @brief Attempts to compile a shader program using the given shaders.
/// This function assumes all given shader ids are valid and as a result it
/// performs no checks to ensure valid id's. This function does not delete the
/// created shader program if compilation would fail. In the event compilation
/// does fail the whether the value of delete_shaders is ignored
/// @param shader_ids The shaders to include in the program
/// @param delete_shaders Determines whether the shaders are deleted once the
/// program has been sucessfully created
/// @return The id of The created shader program
u32 compile_shader_program(const std::vector<u32>& shader_ids,
                           bool delete_shaders = true) noexcept;

/// @brief Attempts to compile the given shader. This function does
/// not delete the created shader if compilation would fail
/// @param shader The shader to create
/// @return The id of the created shader
u32 compile_shader(const shader_t& shader) noexcept;

/// @brief Attempts to contruct a shader program by calling
/// utils::shader::compile_shader_program using the given shaders that were
/// successfully compiled through a call to utils::shader::create_shader and
/// utils::shader::shader_compiled afterward in order This function calls
/// utils::shader::compile_shader_program with delete_shaders as false
/// @return The result of the program's creation where
/// x may be: the program's id
/// y may be: a vector of the id's of shaders that failed to compile or nothing
shader_compile_result_t
make_shader_program(const std::vector<shader_t>& shaders) noexcept;

} // namespace utils::shader
