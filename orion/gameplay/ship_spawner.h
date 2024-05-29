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
	ship_spawner() : world(nullptr) {}

	void notify_spawn(const game_block &block);

	void set_listener(subscriber *listener) { world = listener; }

	void set_behavior(spaceship &ship, const behavior_item &item);

	game_object *spawn_object(const vector2f &position, const vector2f &forward_vector) const;
	spaceship *spawn_spaceship(const vector2f &position, const vector2f &forward_vector) const;

private:
	subscriber *world;

	float calculate_coordinate(const range_container &range);
};
#endif // SHIP_SPAWNER_H
