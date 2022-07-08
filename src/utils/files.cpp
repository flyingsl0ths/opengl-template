#include <fstream>
#include <iostream>
#include <sstream>

#include "files.hpp"

namespace utils::files
{

std::string read_file(std::string file_path)
{
    std::string file_contents {};

    std::ifstream file;

    // ensure ifstream objects can throw exceptions:
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    auto const read_file_contents = [&, file_path]()
    {
        file.open(file_path.data());

        std::stringstream f_stream;

        f_stream << file.rdbuf();

        file.close();

        file_contents = f_stream.str();
    };

    try
    {
        read_file_contents();
    }
    catch (const std::ifstream::failure&)
    {
        std::cerr << file_path << " could not be read\n";
    }

    return file_contents;
}

} // namespace utils::files
