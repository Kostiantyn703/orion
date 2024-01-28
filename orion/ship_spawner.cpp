#include "ship_spawner.h"

#include "spaceship.h"
#include "resource_module.h"
#include "game_block.h"

ship_spawner::ship_spawner() : m_world(nullptr) {
}

void ship_spawner::notify_spawn(const game_block &in_block) {
	vector2f spawn_pos = vector2f(WINDOW_WIDTH * in_block.m_spawn_pos, -OUT_OFFSET);
	
	std::string tex_name;
	if (in_block.m_type == 0) tex_name = TEX_NAME_ENEMY_00;
	if (in_block.m_type == 1) tex_name = TEX_NAME_ENEMY_01;
	texture *cur_tex = resource_module::get_instance()->get_texture(tex_name);

	vector2f forward_vec(0.f, 1.f);
	spaceship *enemy = spawn_spaceship(spawn_pos, forward_vec);
	enemy->set_texture(cur_tex);
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