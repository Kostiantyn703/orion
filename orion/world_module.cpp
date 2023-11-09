#include "world_module.h"

#include "globals.h"
#include "resource_module.h"

world_module::~world_module() {
	for (auto it = m_objects.begin(); it != m_objects.end(); ++it) {
		delete *it;
	}
	m_objects.clear();
}

void world_module::init_player(controller *in_controller) {
	point player_pos(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.8f);
	game_object *player =  create_object(player_pos);
	texture *player_tex = resource_module::get_instance()->get_texture(TEX_NAME_SHIP);
	player->set_texture(player_tex);
	in_controller->set_owner(player);
	player->subscribe(this);
	m_objects.push_back(player);
}

void world_module::init_objects() {
	point enemy_pos(WINDOW_WIDTH * 0.75f, WINDOW_HEIGHT * 0.2f);
	game_object *enemy = create_object(enemy_pos);
	texture *enemy_tex = resource_module::get_instance()->get_texture(TEX_NAME_ENEMY);
	enemy->set_texture(enemy_tex);
	m_objects.push_back(enemy);

	point meteor_pos(WINDOW_WIDTH * 0.4f, WINDOW_HEIGHT * 0.1f);
	game_object *meteor = create_object(meteor_pos);
	texture *meteor_tex = resource_module::get_instance()->get_texture(TEX_NAME_METEOR_BROWN_BIG);
	meteor->set_texture(meteor_tex);
	m_objects.push_back(meteor);
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

void world_module::spawn_bullet(const point &in_position) {
	game_object *bullet = create_object(in_position);
	bullet->set_texture(resource_module::get_instance()->get_texture(TEX_NAME_BULLET));
	bullet->set_velocity(BULLET_VELOCITY);
	bullet->set_type(object_type::OT_BULLET);
	bullet->move_forward();
	m_objects.push_back(bullet);
}

void world_module::on_notify(game_object *in_object) {
 	spawn_bullet(in_object->get_position());
}
