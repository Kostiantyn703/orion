#ifndef SHIP_SPAWNER_H
#define SHIP_SPAWNER_H

#include "globals.h"
#include "game_object.h"
#include "spaceship.h"
#include "subscriber.h"

struct game_block;

class ship_spawner {
public:
	ship_spawner();
	~ship_spawner() {}

	void notify_spawn(const game_block &in_block);

	void set_listener(subscriber *in_listener) { m_world = in_listener; }

	void set_behavior(spaceship &in_ship, const game_block &in_block);

	game_object *spawn_object(const vector2f &in_position, const vector2f &in_forward_vector) const;
	spaceship *spawn_spaceship(const vector2f &in_position, const vector2f &in_forward_vector) const;

private:
	subscriber *m_world;
};

#endif // SHIP_SPAWNER_H
