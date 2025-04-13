#include <fstream>
#include <iostream>
#include <sstream>

#include "files.hpp"

namespace glaze::files {

std::string read_file(std::string const& file_path) {
	std::string file_contents{};

	std::ifstream file;

	// ensure ifstream objects can throw exceptions:
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	file.open(file_path.data());

	std::stringstream f_stream;

	f_stream << file.rdbuf();

	file.close();

	file_contents = f_stream.str();

	return file_contents;
}

} // namespace glaze::files
