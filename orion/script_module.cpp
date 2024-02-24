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

script_module::script_module() {}

script_module::~script_module() {}

void script_module::collect_scripts(const std::string &in_path, std::vector<game_block> &out_data) {
	for (const dir_entry &file : dir_it(in_path)) {
		std::string file_path = file.path().string();
		if (file_path.empty()) {
			continue;
		}
		std::string file_content;
		if (get_file_content(file_path, file_content)) {
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
	size_t items_idx = size_t_max;
	for (std::string line; std::getline(input, line);) {
		if (line.empty())	continue;
		erase_spaces				(line);

		size_t idx = line.find("type");
		if (idx != size_t_max) {
			out_block.m_type = parse_int(line);
			continue;
		}
		idx = line.find("shoot");
		if (idx != size_t_max) {
			out_block.is_shooter = true;
		}
		idx = line.find("spawn");
		if (idx != size_t_max) {
			behavior_item beh_item;
			parse_spawn(line, beh_item);
			out_block.add_item(beh_item);
			++items_idx;
			continue;
		}
		idx = line.find("behavior");
		if (idx != size_t_max) {
			if (!out_block.m_items.empty()) {
				parse_behavior(line, out_block.m_items[items_idx]);
			}
		}
	}
}

void script_module::parse_spawn(std::string &in_line, behavior_item &out_item) {
	char token = '=';
	size_t idx = in_line.find(token);
	if (idx == size_t_max) {
		SDL_Log("Bad token.");
	}
	std::string sub = in_line.substr(idx+1, in_line.size()-1);
	if (sub.front() == '[') {
		parse_range(sub, out_item.m_spawn_range);
	} else {
		out_item.m_spawn_pos = (float)std::atof(sub.c_str());
	}
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

void script_module::parse_behavior(std::string &in_line, behavior_item &out_item) {
	char token = '=';
	size_t idx = in_line.find(token);
	++idx;
	in_line.erase(in_line.begin(),in_line.begin() + idx);

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
		behavior_data beh_data;
		for (std::string inner_line; std::getline(inner_ss, inner_line, ',');) {
			if (action_found(inner_line)) {
				beh_data.m_action_name = inner_line;
				continue;
			}
			if (condition_found(inner_line)) {
				beh_data.m_condition_name = inner_line;
				continue;
			}
			if (inner_line.front() == '[') {
				parse_range(inner_line, beh_data.m_range);
			} else {
				beh_data.m_condition_data = (float)std::atof(inner_line.c_str());
			}
		}
		out_item.m_behavior_data.push_back(beh_data);
	}
}

void script_module::parse_range(std::string &in_line, range &out_range) {
	char token = '-';
	size_t tok_idx = in_line.find(token);

	std::string min_val = in_line.substr(1, tok_idx - 1);
	std::string max_val = in_line.substr(tok_idx + 1, in_line.size() - 1);

	out_range.m_min = std::atoi(min_val.c_str());
	out_range.m_max = std::atoi(max_val.c_str());
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

void script_module::erase_spaces(std::string &out_line) {
	auto space_pred = [](int x) { return std::isspace(x); };
	out_line.erase(
		std::remove_if(out_line.begin(), out_line.end(), space_pred)
		, out_line.end()
	);
}
