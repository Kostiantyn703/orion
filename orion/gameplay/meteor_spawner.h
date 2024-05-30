#ifndef METEOR_SPAWNER_H
#define METEOR_SPAWNER_H

#include "../objects/game_object.h"
#include "../interfaces/subscriber.h"

class meteor_spawner {
public:
	meteor_spawner();

	void update(float delta_time);
	void spawn(const float x);

	void set_listener(subscriber *listener) { world = listener; }

	void set_spawn_time(float time) { spawn_time = time; }
	float get_max_spawn_time() const { return max_spawn_time; }

	bool spawn_timer_expired() const { return spawn_time < 0.f; }
	void reload_timer() { spawn_time = max_spawn_time; }

	void set_velocity(float val) { meteor_velocity = val; }
	float get_velocity() const { return meteor_velocity; }

	game_object *create_object(const vector2f &position, const vector2f &forward_vector) const;
private:
	subscriber *world;

	float meteor_velocity;
	float spawn_time;
	float max_spawn_time;
	int spawn_range;

	vector2f calculate_position(const float x);
};
#endif // METEOR_SPAWNER_H