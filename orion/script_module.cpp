#include "script_module.h"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>

#include "SDL_Log.h"

using dir_entry	= std::filesystem::directory_entry;
using dir_it	= std::filesystem::directory_iterator;

script_module::script_module() {
	SDL_Log("Script module constructed");
}

script_module::~script_module() {
}

void script_module::collect_scripts(const std::string &in_path, std::vector<float> &out_data) {
	SDL_Log("The path to collect [%s]", in_path.c_str());

	for (const dir_entry &file : dir_it(in_path)) {
		std::string file_path = file.path().string();
		if (file_path.empty()) {
			continue;
		}
		SDL_Log("Found file [%s]", file_path.c_str());
		std::string file_content;
		if (get_file_content(file_path, file_content)) {
			SDL_Log("File content \n%s", file_content.c_str());
			float res = parse_float(file_content);
			out_data.push_back(res);
		}
	}
}

bool script_module::get_file_content(const std::string &in_file, std::string &out_content) {
	std::ifstream read_stream(in_file);
	if (!read_stream.is_open()) {
		SDL_LogError(0, "Failed load data from file [%s]", in_file.c_str());
		return false;
	}

	std::stringstream str_stream;
	str_stream << read_stream.rdbuf();
	out_content = str_stream.str();
	return true;
}

float script_module::parse_float(std::string &in_line) {
	char token = '=';
	size_t idx = in_line.find(token);
	if (idx == std::numeric_limits<size_t>::max()) {
		SDL_Log("Bad token.");
	}
	std::string sub = in_line.substr(idx+1, in_line.size()-1);
	float result = std::atof(sub.c_str());
	return result;
}
