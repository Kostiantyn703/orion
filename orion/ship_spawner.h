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
	~ship_spawner();

	void set_spawn_pos(float in_x, float in_y) { m_spawn_pos = vector2f(in_x, in_y); }
	const vector2f get_spawn_pos() const { return m_spawn_pos; }

	void gather_script_data(const game_block &in_block);

	void notify();

	void set_listener(subscriber *in_listener) { m_world = in_listener; }

	game_object *spawn_object(const vector2f &in_position, const vector2f &in_forward_vector) const;

	spaceship *spawn_spaceship(const vector2f &in_position, const vector2f &in_forward_vector) const;

private:
	vector2f m_spawn_pos;
	texture *m_cur_tex = nullptr;

	subscriber *m_world;
};

#endif // SHIP_SPAWNER_H
