#include "ship_spawner.h"

#include "spaceship.h"
#include "resource_module.h"

ship_spawner::ship_spawner() : m_world(nullptr) {
	m_controller = new enemy_controller();
}

ship_spawner::~ship_spawner() {
	delete m_controller;
}

void ship_spawner::update(float delta_time) {
	m_spawn_time -= delta_time;
	if (m_counter == 0 ) return;
	if (m_spawn_time < 0.f) {
		m_spawn_time = m_max_spawn_time;
		notify();
	}
	m_controller->update(delta_time);
}

void ship_spawner::notify() {
	vector2f pos(WINDOW_WIDTH * 0.8f, -20.f);
	vector2f forward_vec(0.f, 1.f);
	spaceship *enemy = spawn_spaceship(pos, forward_vec);
	texture *tex = resource_module::get_instance()->get_texture(TEX_NAME_ENEMY);
	enemy->set_texture(tex);
	enemy->on_spawn();
	enemy->set_mask(MASK_ENEMY);
	m_world->on_notify(*enemy);
	--m_counter;
	if (!m_controller->get_owner()) {
		m_controller->set_owner(enemy);
	}
}

game_object *ship_spawner::spawn_object(const vector2f &in_position, const vector2f &in_forward_vector) const {
	return new spaceship(in_position, in_forward_vector);
}

spaceship *ship_spawner::spawn_spaceship(const vector2f &in_position, const vector2f &in_forward_vector) const {
	return new spaceship(in_position, in_forward_vector);
}