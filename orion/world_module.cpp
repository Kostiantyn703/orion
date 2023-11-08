#include "world_module.h"

#include "globals.h"

world_module::world_module() {}
world_module::~world_module() {}

void world_module::init_player(controller *in_controller, const resource_module &in_resources) {
	point player_pos(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.8f);
	game_object *player =  create_object(player_pos);
	player->set_texture(in_resources.get_texture(TEX_NAME_SHIP));
	in_controller->set_owner(player);
	m_objects.push_back(player);
}

void world_module::init_objects(const resource_module &in_resources) {
	point enemy_pos(WINDOW_WIDTH * 0.75f, WINDOW_HEIGHT * 0.2f);
	game_object *enemy = create_object(enemy_pos);
	enemy->set_texture(in_resources.get_texture(TEX_NAME_ENEMY));
	m_objects.push_back(enemy);

	point meteor_pos(WINDOW_WIDTH * 0.4f, WINDOW_HEIGHT * 0.1f);
	game_object *meteor = create_object(meteor_pos);
	meteor->set_texture(in_resources.get_texture(TEX_NAME_METEOR_BROWN_BIG));
	m_objects.push_back(meteor);

	point bullet_pos(WINDOW_WIDTH * 0.15f, WINDOW_HEIGHT * 0.9f);
	game_object * bullet = create_object(bullet_pos);
	bullet->set_texture(in_resources.get_texture(TEX_NAME_BULLET));
	bullet->set_velocity(1000.f);
	bullet->set_type(object_type::OT_BULLET);
	bullet->move_forward();
	m_objects.push_back(bullet);
}

void world_module::update(float delta_time) {
	for (object_storage::const_iterator it = m_objects.cbegin(); it != m_objects.cend(); ++it) {
		(*it)->update(delta_time);
	}
}

game_object	*world_module::create_object(float in_x, float in_y) const {
	return new game_object(in_x, in_y);
}

game_object *world_module::create_object(const point &in_position) const {
	return new game_object(in_position);
}
