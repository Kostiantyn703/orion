#include "script_module.h"
#include <filesystem>

using dir_entry	= std::filesystem::directory_entry;
using dir_it	= std::filesystem::directory_iterator;

script_module::script_module() {
	SDL_Log("Script module constructed");
}

script_module::~script_module() {
}

void script_module::collect_scripts(const std::string &in_path) {
	SDL_Log("The path to collect [%s]", in_path.c_str());

	for (const dir_entry &file : dir_it(in_path)) {
		std::string file_name = file.path().string();
		SDL_Log("Found file [%s]", file_name.c_str());
	}
}
