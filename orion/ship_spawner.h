#ifndef SHIP_SPAWNER_H
#define SHIP_SPAWNER_H

#include "globals.h"
#include "game_object.h"
#include "spaceship.h"
#include "subscriber.h"

class ship_spawner {
public:
	ship_spawner();
	~ship_spawner();

	void update(float delta_time);

	void notify();

	void set_listener(subscriber *in_listener) { m_world = in_listener; }

	game_object *spawn_object(const vector2f &in_position, const vector2f &in_forward_vector) const;
	// TODO: temporary for player
	spaceship *spawn_spaceship(const vector2f &in_position, const vector2f &in_forward_vector) const;

private:
	float m_max_spawn_time = 7.f;
	float m_spawn_time = 0.f;
	// temp variable 
	size_t m_counter = 5;

	subscriber *m_world;
};

#endif // SHIP_SPAWNER_H
