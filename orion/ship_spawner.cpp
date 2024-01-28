#include "ship_spawner.h"

#include "spaceship.h"
#include "resource_module.h"

ship_spawner::ship_spawner() : m_world(nullptr) {
}

ship_spawner::~ship_spawner() {
}

void ship_spawner::update(float delta_time) {
	m_spawn_time -= delta_time;
	if (m_spawn_time < 0.f) {
		m_spawn_time = m_max_spawn_time;
		notify();
	}
}

void ship_spawner::gather_script_data(const float in_script_data) {
	m_spawn_pos = vector2f(WINDOW_WIDTH * in_script_data, -OUT_OFFSET);
}

void ship_spawner::notify() {
	vector2f forward_vec(0.f, 1.f);
	spaceship *enemy = spawn_spaceship(m_spawn_pos, forward_vec);
	texture *tex = resource_module::get_instance()->get_texture(TEX_NAME_ENEMY);
	enemy->set_texture(tex);
	enemy->on_spawn();
	// setting the behavior
	action act1;
	act1.set_type(action_type::AT_MOVE_FORWARD);
	enemy->get_behavior()->add_action(act1);
	enemy->get_behavior()->init();
	m_world->on_notify(*enemy);
}

game_object *ship_spawner::spawn_object(const vector2f &in_position, const vector2f &in_forward_vector) const {
	return new spaceship(in_position, in_forward_vector);
}

spaceship *ship_spawner::spawn_spaceship(const vector2f &in_position, const vector2f &in_forward_vector) const {
	return new spaceship(in_position, in_forward_vector);
}