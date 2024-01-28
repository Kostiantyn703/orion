#ifndef GAME_BLOCK_H
#define GAME_BLOCK_H

#include <limits>
#include <string>
#include <vector>

struct behavior_data {
	std::string m_action_name;
	std::string m_condition_name;
	float m_condition_data;
};

struct game_block {
	float m_spawn_pos = 0.f;
	size_t m_type = std::numeric_limits<size_t>::max();
	std::vector<behavior_data> m_behavior_data;
};

#endif // GAME_BLOCK_H