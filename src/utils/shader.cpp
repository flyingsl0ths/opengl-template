#include "shader.hpp"

namespace utils::shader
{

std::optional<shader_t> make_shader(std::string  source,
                                    GLenum const type) noexcept
{
    return (source.empty() && type == 0
                ? std::optional<shader_t>()
                : std::optional<shader_t>({std::move(source), type}));
}

bool shader_compiled(u32 const shader_id) noexcept
{
    if (shader_id == SHADER_ERROR) { return false; }

    s32 success {};

    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

    return (success != SHADER_ERROR);
}

bool shader_program_compiled(u32 const shader_program_id) noexcept
{
    if (shader_program_id == SHADER_ERROR) { return false; }

    s32 success {};

    glGetProgramiv(shader_program_id, GL_LINK_STATUS, &success);

    return (success != SHADER_ERROR);
}

void delete_shader_program(u32 const               shader_program_id,
                           const std::vector<u32>& shader_ids) noexcept
{
    for (u32 const shader_id : shader_ids) { glDeleteShader(shader_id); }

    glDeleteProgram(shader_program_id);
}

u32 compile_shader_program(const std::vector<u32>& shader_ids,
                           bool const              delete_shaders) noexcept
{
    u32 const program_id = glCreateProgram();

    for (u32 const shader_id : shader_ids)
    {
        glAttachShader(program_id, shader_id);
    }

    glLinkProgram(program_id);

    if (!shader_program_compiled(program_id)) { return program_id; }

    if (delete_shaders)
    {
        for (u32 shader_id : shader_ids) { glDeleteShader(shader_id); }
    }

    return program_id;
}

u32 compile_shader(const shader_t& shader) noexcept
{
    u32 const shader_id = glCreateShader(shader.second);

    if (shader_id == SHADER_ERROR) { return SHADER_ERROR; }

    const auto* source_code {shader.first.data()};

    glShaderSource(shader_id, 1, &source_code, nullptr);

    glCompileShader(shader_id);

    return shader_id;
}

shader_compile_result_t
make_shader_program(const std::vector<shader_t>& shaders) noexcept
{

    std::vector<u32> creations {};
    creations.reserve(shaders.size());

    using failed_compilations_t = std::vector<u32>;
    failed_compilations_t failures {};

    auto const on_compiled_shader =
        [&creations, &failures](const shader_t& shader)
    {
        u32 const shader_id = compile_shader(shader);

        ((shader_compiled(shader_id)) ? creations : failures)
            .push_back(shader_id);
    };

    for (const auto& shader : shaders) { on_compiled_shader(shader); }

    return {compile_shader_program(creations, false),
            (failures.empty()
                 ? std::optional<failed_compilations_t>()
                 : std::optional<failed_compilations_t>(failures))};
}

} // namespace utils::shader
