#include "world_module.h"

#include "globals.h"

world_module::world_module() {}
world_module::~world_module() {}

void world_module::init_player(controller *in_controller, const resource_module &in_resources) {
	point player_pos(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.8f);
	create_object(object_type::OT_PLAYER, player_pos, in_resources.get_texture(TEX_NAME_SHIP));
	in_controller->set_owner(*m_objects.begin());
}

void world_module::init_objects(const resource_module &in_resources) {
	point enemy_pos(WINDOW_WIDTH * 0.75f, WINDOW_HEIGHT * 0.2f);
	create_object(object_type::OT_ENEMY, enemy_pos, in_resources.get_texture(TEX_NAME_ENEMY));
	point meteor_pos(WINDOW_WIDTH * 0.4f, WINDOW_HEIGHT * 0.1f);
	create_object(object_type::OT_METEOR, meteor_pos, in_resources.get_texture(TEX_NAME_METEOR_BROWN_BIG));
	point bullet_pos(WINDOW_WIDTH * 0.15f, WINDOW_HEIGHT * 0.5f);
	create_object(object_type::OT_BULLET, bullet_pos, in_resources.get_texture(TEX_NAME_BULLET));
}


void world_module::update(float delta_time) {
	for (object_storage::const_iterator it = m_objects.cbegin(); it != m_objects.cend(); ++it) {
		(*it)->update(delta_time);
	}
}

void world_module::create_object(float in_x, float in_y, texture *in_texture) {
	game_object *object = new game_object(in_x, in_y);
	object->set_texture(in_texture);
	m_objects.push_back(object);
}

void world_module::create_object(object_type in_type, point &in_position, texture *in_texture) {
	game_object *object = new game_object(in_type);
	object->set_position(in_position);
	object->set_texture(in_texture);

	m_objects.push_back(object);
}
