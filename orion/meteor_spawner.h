#ifndef METEOR_SPAWNER_H
#define METEOR_SPAWNER_H

#include "game_object.h"
#include "subscriber.h"

class meteor_spawner {
public:
	meteor_spawner() : m_spawn_time(m_max_spawn_time) {}
	~meteor_spawner() {}

	void update(float delta_time);
	void notify();

	void set_listener(subscriber *in_listener) { m_world = in_listener; }

	game_object *spawn_object(const vector2f &in_position, const vector2f &in_forward_vector) const;
private:
	subscriber *m_world;

	float m_max_spawn_time = 50.f;
	float m_spawn_time = 0.f;

	vector2f calculate_position();

};
#endif // METEOR_SPAWNER_H