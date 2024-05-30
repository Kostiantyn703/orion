#ifndef game_block_H
#define game_block_H

#include <limits>
#include <string>
#include <vector>

#include "../utils/globals.h"

struct behavior_data {
	std::string	action_name;
	std::string	condition_name;

	range_container	range;
	float condition_data = 0.f;
};

struct behavior_item {
	float spawn_pos_x = 0.f;
	range_container spawn_range;

	std::vector<behavior_data> behavior;
};

struct game_block {
	size_t type = std::numeric_limits<size_t>::max();
	bool is_shooter = false;
	std::vector<behavior_item> items;

	void add_item(const behavior_item &item) { items.push_back(item); }
};
#endif // game_block_H