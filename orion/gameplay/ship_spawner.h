#ifndef SHIP_SPAWNER_H
#define SHIP_SPAWNER_H

#include "../objects/game_object.h"
#include "../objects/spaceship.h"

#include "../interfaces/subscriber.h"

#include "../utils/globals.h"

struct behavior_item;
struct game_block;

class ship_spawner {
public:
	ship_spawner() : m_world(nullptr) {}
	~ship_spawner() {}

	void notify_spawn(const game_block &in_block);

	void set_listener(subscriber *in_listener) { m_world = in_listener; }

	void set_behavior(spaceship &in_ship, const behavior_item &in_item);

	game_object *spawn_object(const vector2f &in_position, const vector2f &in_forward_vector) const;
	spaceship *spawn_spaceship(const vector2f &in_position, const vector2f &in_forward_vector) const;

private:
	subscriber *m_world;

	float calculate_coordinate(const range &in_range);
};
#endif // SHIP_SPAWNER_H
