#include <exception>
#include "app.hpp"
#include "common.hpp"

#include <forest/forest.hpp>

namespace {

inline std::string red_text(str text) {
	return std::string("<rgb=500><b>") + text.data();
}

} // namespace

s32 main(s32 const argc, char* const argv[]) {
	try {
		app_t app{std::span<char* const>(argv, static_cast<usize>(argc))};
		app.run();
	} catch (std::exception const& e) {
		forest::print_to(stderr, red_text(e.what()));
		return -1;
	}

	return 0;
}
