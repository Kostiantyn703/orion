#ifndef SCRIPT_MODULE_H
#define SCRIPT_MODULE_H

#include <string>
#include <vector>

#include "../gameplay/game_block.h"

struct game_block;
struct behavior_item;

class script_module {
	using string_vector = std::vector<std::string>;
public:
	void collect_scripts(const std::string &path, std::vector<game_block> &data);

private:
	bool get_file_content(const std::string &file, std::string &content);
	void parse_file_content(std::string &content, game_block &block);

	void erase_spaces(std::string &line);
	
	size_t parse_int(std::string &line);
	void parse_spawn_position(std::string &line, behavior_item &item);
	
	std::string get_data_substring(std::string &line) const;
	
	void parse_behavior(std::string &line, behavior_item &item);

	bool token_found(const std::string &line, string_vector &values);

	void parse_range(std::string &line, range_container &range);
	
	string_vector actions = { ACTION_FORWARD, ACTION_LEFT, ACTION_RIGHT, ACTION_BACKWARD };
	string_vector conditions = { X_POS, Y_POS };
};
#endif // SCRIPT_MODULE_H
