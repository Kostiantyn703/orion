#include "meteor_spawner.h"

#include <cstdlib>

#include "../objects/meteor.h"
#include "../modules/resource_module.h"
#include "../utils/globals.h"

meteor_spawner::meteor_spawner() : m_world(nullptr) {
	m_max_spawn_time = METEOR_MAX_SPAWN_TIME;
	m_spawn_range = METEOR_SPAWN_RANGE;
	m_spawn_time = m_max_spawn_time;
	m_meteor_velocity = METEOR_VELOCITY;
}

void meteor_spawner::update(float delta_time) {
	m_spawn_time -= delta_time;
}

void meteor_spawner::spawn(const float x) {
	reload_timer();

	texture *meteor_tex_big = resource_module::get_instance()->get_texture(TEX_NAME_METEOR_BROWN_BIG);

	vector2f forward_vec(0.f, 1.f);
	vector2f pos(calculate_position(x));
	game_object *object = create_object(pos, forward_vec, m_meteor_velocity);
	object->set_texture(meteor_tex_big);
	object->set_mask(MASK_ENEMY);
	object->init();
	m_world->on_notify(*object);
}

game_object *meteor_spawner::create_object(const vector2f &position, const vector2f &forward_vector, const float velocity) const {
	return new meteor(position, forward_vector, velocity);
}

vector2f meteor_spawner::calculate_position(const float x) {
	float area = x - (m_spawn_range / 2.f);
	int x_rand = std::rand() % int(m_spawn_range);
	float y_val = -OUT_OFFSET;

	return vector2f(float(area + x_rand), y_val);
}