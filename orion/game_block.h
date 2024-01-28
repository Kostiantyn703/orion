#ifndef GAME_BLOCK_H
#define GAME_BLOCK_H

#include <limits>

struct game_block {
	float m_spawn_pos = 0.f;
	size_t m_type = std::numeric_limits<size_t>::max();

};

#endif // GAME_BLOCK_H