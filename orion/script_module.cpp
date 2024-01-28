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

void script_module::collect_scripts(const std::string &in_path, std::vector<game_block> &out_data) {
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
			game_block cur_block;
			parse_file_content(file_content, cur_block);
			out_data.push_back(cur_block);
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

void script_module::parse_file_content(std::string &in_content, game_block &out_block) {
	char end_line_token = '\n';
	size_t end_line_idx = in_content.find_first_of('\n');
	std::string sub1 = in_content.substr(0, end_line_idx);
	++end_line_idx;
	out_block.m_spawn_pos = parse_float(sub1);
	std::string sub2 = in_content.substr(end_line_idx, sub1.find_first_of(end_line_token));
	out_block.m_type = parse_int(sub2);
}

float script_module::parse_float(std::string &in_line) {
	char token = '=';
	size_t idx = in_line.find(token);
	if (idx == std::numeric_limits<size_t>::max()) {
		SDL_Log("Bad token.");
	}
	std::string sub = in_line.substr(idx+1, in_line.size()-1);
	float result = (float)std::atof(sub.c_str());
	return result;
}

size_t script_module::parse_int(std::string &in_line) {
	char token = '=';
	size_t idx = in_line.find(token);
	if (idx == std::numeric_limits<size_t>::max()) {
		SDL_Log("Bad token.");
	}
	std::string sub = in_line.substr(idx + 1, in_line.size() - 1);
	size_t result = std::atoi(sub.c_str());
	return result;
}
