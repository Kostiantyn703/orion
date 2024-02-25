#ifndef METEOR_SPAWNER_H
#define METEOR_SPAWNER_H

#include "../objects/game_object.h"
#include "../interfaces/subscriber.h"

class meteor_spawner {
public:
	meteor_spawner();
	~meteor_spawner() {}

	void update(float delta_time);
	void notify();

	void set_listener(subscriber *in_listener) { m_world = in_listener; }

	void set_spawn_time(float in_time) { m_spawn_time = in_time; }
	float get_max_spawn_time() const { return m_max_spawn_time; }

	bool spawn_timer_expired() const { return m_spawn_time < 0.f; }
	void reload_timer() { m_spawn_time = m_max_spawn_time; }

	void set_spawn_pos(float in_x) { m_spawn_x = in_x; }

	void set_velocity(float in_val) { m_meteor_velocity = in_val; }
	float get_velocity() const { return m_meteor_velocity; }

	game_object *spawn_object(const vector2f &in_position, const vector2f &in_forward_vector, const float in_velocity) const;
private:
	subscriber *m_world;

	float m_meteor_velocity = 0.f;

	float m_spawn_x = 0.f;
	float m_spawn_time = 0.f;

	float m_max_spawn_time = 0.f;

	int m_spawn_range = 0;

	vector2f calculate_position();

};
#endif // METEOR_SPAWNER_H