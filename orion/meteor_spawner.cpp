#include "meteor_spawner.h"

#include <cstdlib>

#include "meteor.h"
#include "resource_module.h"

void meteor_spawner::update(float delta_time) {
	m_spawn_time -= delta_time;
	if (m_spawn_time < 0.f) {
		m_spawn_time = m_max_spawn_time;
		notify();
	}
}

void meteor_spawner::notify() {
	texture *meteor_tex_big = resource_module::get_instance()->get_texture(TEX_NAME_METEOR_BROWN_BIG);

	vector2f forward_vec(0.f, 1.f);
	vector2f pos(calculate_position());
	game_object *object = spawn_object(pos, forward_vec);
	object->set_texture(meteor_tex_big);
	object->set_mask(MASK_ENEMY);
	object->init();

	m_world->on_notify(*object);
}

game_object *meteor_spawner::spawn_object(const vector2f &in_position, const vector2f &in_forward_vector) const {
	return new meteor(in_position, in_forward_vector);
}

vector2f meteor_spawner::calculate_position() {
	int x_rand = std::rand() % int(WINDOW_WIDTH - 20);
	float y_val = -20.f;

	return vector2f(float(x_rand), y_val);
}