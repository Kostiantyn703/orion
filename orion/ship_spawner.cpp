#include "ship_spawner.h"

#include "spaceship.h"
#include "resource_module.h"

void ship_spawner::update(float delta_time) {
	
}

void ship_spawner::notify() {
	vector2f pos(WINDOW_WIDTH * 0.8f, WINDOW_HEIGHT * 0.2f);
	vector2f forward_vec(0.f, 1.f);
	game_object *enemy = spawn_object(pos, forward_vec);
	texture *tex = resource_module::get_instance()->get_texture(TEX_NAME_ENEMY);
	enemy->set_texture(tex);
	//enemy//->on_spawn()
	m_world->on_notify(*enemy);
}

game_object *ship_spawner::spawn_object(const vector2f &in_position, const vector2f &in_forward_vector) const {
	return new spaceship(in_position, in_forward_vector);
}

spaceship *ship_spawner::spawn_spaceship(const vector2f &in_position, const vector2f &in_forward_vector) const {
	return new spaceship(in_position, in_forward_vector);
}