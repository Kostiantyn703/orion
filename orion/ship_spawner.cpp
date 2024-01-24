#include "ship_spawner.h"

#include "spaceship.h"
#include "resource_module.h"

ship_spawner::ship_spawner() : m_world(nullptr) {
	m_spawn_pos = vector2f(WINDOW_WIDTH * 0.8f, -OUT_OFFSET);
}

ship_spawner::~ship_spawner() {
}

void ship_spawner::update(float delta_time) {
	m_spawn_time -= delta_time;
	if (m_counter == 0) {
		m_counter = 5;
		if (!changed) {
			m_spawn_pos = vector2f(WINDOW_WIDTH * 0.2f, -OUT_OFFSET);
			changed = true;
		}
		else {
			m_spawn_pos = vector2f(WINDOW_WIDTH * 0.8f, -OUT_OFFSET);
			changed = false;
		}
		m_spawn_time = m_max_spawn_time;
		return;
	}
	if (m_spawn_time < 0.f) {
		m_spawn_time = m_max_spawn_time;
		notify();
	}
}

void ship_spawner::notify() {
	vector2f pos(m_spawn_pos);
	vector2f forward_vec(0.f, 1.f);
	spaceship *enemy = spawn_spaceship(pos, forward_vec);
	texture *tex = resource_module::get_instance()->get_texture(TEX_NAME_ENEMY);
	enemy->set_texture(tex);
	enemy->on_spawn();
	// setting the behavior
	action act1;
	act1.set_type(action_type::AT_MOVE_FORWARD);

	enemy->get_behavior()->add_action(act1);
	m_world->on_notify(*enemy);

	--m_counter;
}

game_object *ship_spawner::spawn_object(const vector2f &in_position, const vector2f &in_forward_vector) const {
	return new spaceship(in_position, in_forward_vector);
}

spaceship *ship_spawner::spawn_spaceship(const vector2f &in_position, const vector2f &in_forward_vector) const {
	return new spaceship(in_position, in_forward_vector);
}