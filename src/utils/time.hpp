#pragma once

#include <chrono>

#include <common.hpp>

namespace glaze::utils::time
{

using timer         = std::chrono::steady_clock;
using time_point    = timer::time_point;
using duration_type = f32;
using duration      = std::chrono::duration<duration_type>;

inline duration_type delta_time(time_point const then,
                                time_point const now = timer::now())
{
    return std::chrono::duration_cast<duration>(now - then).count();
}

} // namespace glaze::utils::time
