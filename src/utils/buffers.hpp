#pragma once

#include <array>
#include <type_traits>

#include <common.hpp>

#include <glad/glad.h>

namespace utils
{

/// @brief Constructs a single or multiple VBO(s)
template <s32 total>
auto make_vbos() -> std::
    conditional_t<total == 1, u32, std::array<u32, static_cast<szt>(total)>>
{

    if constexpr (total == 1)
    {
        u32 vbo {};
        glGenBuffers(1, &vbo);
        return vbo;
    }
    else
    {
        std::array<u32, static_cast<szt>(total)> vbo {};
        glGenBuffers(total, vbo.data());
        return vbo;
    }
}

} // namespace utils
