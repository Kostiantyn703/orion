#include "script_module.h"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>

#include "SDL_Log.h"
#include <algorithm>
#include <cctype>


using dir_entry	= std::filesystem::directory_entry;
using dir_it	= std::filesystem::directory_iterator;

const size_t size_t_max	= std::numeric_limits<size_t>::max();

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
	std::istringstream input;
	input.str(in_content);
	for (std::string line; std::getline(input, line);) {
		size_t idx = line.find("spawn");
		if (idx != size_t_max) {
			out_block.m_spawn_pos = parse_float(line);
			continue;
		}
		idx = size_t_max;
		idx = line.find("type");
		if (idx != size_t_max) {
			out_block.m_type = parse_int(line);
			continue;
		}
		idx = size_t_max;
		idx = line.find("behavior");
		if (idx != size_t_max) {
			parse_behavior(line, out_block);
		}
	}
}

float script_module::parse_float(std::string &in_line) {
	char token = '=';
	size_t idx = in_line.find(token);
	if (idx == size_t_max) {
		SDL_Log("Bad token.");
	}
	std::string sub = in_line.substr(idx+1, in_line.size()-1);
	float result = (float)std::atof(sub.c_str());
	return result;
}

size_t script_module::parse_int(std::string &in_line) {
	char token = '=';
	size_t idx = in_line.find(token);
	if (idx == size_t_max) {
		SDL_Log("Bad token.");
	}
	std::string sub = in_line.substr(idx + 1, in_line.size() - 1);
	size_t result = std::atoi(sub.c_str());
	return result;
}

void script_module::parse_behavior(std::string &in_line, game_block &out_block) {
	char token = '=';
	size_t idx = in_line.find(token);
	++idx;
	in_line.erase(in_line.begin(),in_line.begin() + idx);
	// remove spaces
	auto space_pred = [](size_t x) { return (size_t)std::isspace(x); };
	in_line.erase(
			std::remove_if(in_line.begin(), in_line.end(), space_pred)
		, in_line.end()
	);

	auto brackets_pred = [](char val) { return val == '{' || val == '}'; };
	
	std::istringstream sstream;
	sstream.str(in_line);
	for (std::string line; std::getline(sstream, line, ';');) {
		line.erase(
				std::remove_if(line.begin(), line.end(), brackets_pred)
			,	line.end()
		);
		std::stringstream inner_ss;
		inner_ss.str(line);
		behavior_data item;
		for (std::string inner_line; std::getline(inner_ss, inner_line, ',');) {
			if (action_found(inner_line)) {
				item.m_action_name = inner_line;
				continue;
			}
			if (condition_found(inner_line)) {
				item.m_condition_name = inner_line;
				continue;
			}
			item.m_condition_data = std::atof(inner_line.c_str());
		}
		out_block.m_behavior_data.push_back(item);
	}
}

bool script_module::action_found(const std::string &in_line) {
	for (size_t i = 0; i < m_actions.size(); ++i) {
		size_t idx = in_line.find(m_actions[i]);
		if (idx != size_t_max) {
			return	true;
		}
	}
	return	false;
}

bool script_module::condition_found(const std::string &in_line) {
	for (size_t i = 0; i < m_conditions.size(); ++i) {
		size_t idx = in_line.find(m_conditions[i]);
		if (idx != size_t_max) {
			return	true;
		}
	}
	return	false;

}

