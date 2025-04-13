#pragma once

#include <string>

#include <common.hpp>

namespace glaze::files {

std::string read_file(std::string const& file_path) noexcept(false);

} // namespace glaze::files
