#include "script_module.h"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

#include "SDL_Log.h"

using dir_entry	= std::filesystem::directory_entry;
using dir_it	= std::filesystem::directory_iterator;

const size_t size_t_max	= std::numeric_limits<size_t>::max();

const char SYMBOL_EQUALS = '=';
const char SYMBOL_LEFT_SQUARE_BRACKET = '[';
const char SYMBOL_COMMA = ',';
const char SYMBOL_SEMICOLON = ';';
const char SYMBOL_CURLY_BRACKET_LEFT = '{';
const char SYMBOL_CURLY_BRACKET_RIGHT = '}';
const char SYMBOL_MINUS = '-';

const std::string SCRIPT_TOKEN_TYPE = "type";
const std::string SCRIPT_TOKEN_SHOOT = "shoot";
const std::string SCRIPT_TOKEN_SPAWN = "spawn";
const std::string SCRIPT_TOKEN_BEHAVIOR = "behavior";

void script_module::collect_scripts(const std::string &path, std::vector<game_block> &data) {
	for (const dir_entry &file : dir_it(path)) {
		std::string file_path = file.path().string();
		if (file_path.empty()) {
			continue;
		}
		std::string file_content;
		if (get_file_content(file_path, file_content)) {
			game_block block;
			parse_file_content(file_content, block);
			data.push_back(block);
		}
	}
}

bool script_module::get_file_content(const std::string &file, std::string &content) {
	std::ifstream read_stream(file);
	if (!read_stream.is_open()) {
		SDL_LogError(0, "Failed load data from file [%s]", file.c_str());
		return false;
	}

	std::stringstream str_stream;
	str_stream << read_stream.rdbuf();
	content = str_stream.str();
	return true;
}

void script_module::parse_file_content(std::string &content, game_block &block) {
	std::istringstream input;
	input.str(content);
	size_t items_idx = size_t_max;
	for (std::string line; std::getline(input, line);) {
		if (line.empty())	continue;
		erase_spaces				(line);

		size_t idx = line.find(SCRIPT_TOKEN_TYPE);
		if (idx != size_t_max) {
			block.type = parse_int(line);
			continue;
		}
		idx = line.find(SCRIPT_TOKEN_SHOOT);
		if (idx != size_t_max) {
			block.is_shooter = true;
		}
		idx = line.find(SCRIPT_TOKEN_SPAWN);
		if (idx != size_t_max) {
			behavior_item item;
			parse_spawn_position(line, item);
			block.add_item(item);
			++items_idx;
			continue;
		}
		idx = line.find(SCRIPT_TOKEN_BEHAVIOR);
		if (idx != size_t_max) {
			if (!block.items.empty()) {
				parse_behavior(line, block.items[items_idx]);
			}
		}
	}
}

void script_module::erase_spaces(std::string &out_line) {
	auto space_pred = [](int x) {
		return std::isspace(x);
	};
	std::string::iterator remove_iter = std::remove_if(out_line.begin(), out_line.end(), space_pred);
	out_line.erase(remove_iter, out_line.end());
}

size_t script_module::parse_int(std::string &line) {
	std::string sub = get_data_substring(line);;
	size_t result = std::atoi(sub.c_str());
	return result;
}

void script_module::parse_spawn_position(std::string &line, behavior_item &item) {
	std::string sub = get_data_substring(line);
	if (sub.front() == SYMBOL_LEFT_SQUARE_BRACKET) {
		parse_range(sub, item.spawn_range);
	} else {
		item.spawn_pos_x = (float)std::atof(sub.c_str());
	}
}

std::string script_module::get_data_substring(std::string &line) const {
	size_t idx = line.find(SYMBOL_EQUALS);
	if (idx == size_t_max) {
		SDL_Log("Bad token.");
	}
	size_t next_idx = idx + 1;
	size_t last_idx = line.size() - 1;

	return line.substr(next_idx, last_idx);
}

void script_module::parse_behavior(std::string &line, behavior_item &item) {
	size_t idx = line.find(SYMBOL_EQUALS);
	++idx;
	line.erase(line.begin(),line.begin() + idx);

	auto brackets_pred = [](char val) {
		return val == SYMBOL_CURLY_BRACKET_LEFT || val == SYMBOL_CURLY_BRACKET_RIGHT;
	};
	
	std::istringstream sstream;
	sstream.str(line);
	for (std::string line; std::getline(sstream, line, SYMBOL_SEMICOLON);) {
		std::string::iterator remove_iter = std::remove_if(line.begin(), line.end(), brackets_pred);
		line.erase(remove_iter, line.end());

		std::stringstream inner_ss;
		inner_ss.str(line);
		behavior_data behavior;
		for (std::string inner_line; std::getline(inner_ss, inner_line, SYMBOL_COMMA);) {
			if (token_found(inner_line, actions)) {
				behavior.action_name = inner_line;
				continue;
			}
			if (token_found(inner_line, conditions)) {
				behavior.condition_name = inner_line;
				continue;
			}
			if (inner_line.front() == SYMBOL_LEFT_SQUARE_BRACKET) {
				parse_range(inner_line, behavior.range);
			} else {
				behavior.condition_data = (float)std::atof(inner_line.c_str());
			}
		}
		item.behavior.push_back(behavior);
	}
}

bool script_module::token_found(const std::string &line, string_vector &values) {
	for (size_t i = 0; i < values.size(); ++i) {
		size_t idx = line.find(values[i]);
		if (idx != size_t_max) {
			return	true;
		}
	}
	return	false;
}

void script_module::parse_range(std::string &line, range_container &range) {
	size_t idx = line.find(SYMBOL_MINUS);
	
	size_t min_start_idx = 1;
	size_t min_last_idx = idx - 1;
	std::string min_val = line.substr(min_start_idx, min_last_idx);

	size_t max_start_idx = idx + 1;
	size_t max_last_idx = line.size() - 1;
	std::string max_val = line.substr(max_start_idx, max_last_idx);

	range.min = std::atoi(min_val.c_str());
	range.max = std::atoi(max_val.c_str());
}
