#include "world_module.h"

#include <algorithm>

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
	texture *meteor_tex_big = resource_module::get_instance()->get_texture(TEX_NAME_METEOR_BROWN_BIG);
	texture *meteor_tex_med = resource_module::get_instance()->get_texture(TEX_NAME_METEOR_BROWN_MED);
	
	point meteor_pos1(WINDOW_WIDTH * 0.15f, WINDOW_HEIGHT * 0.2f);
	game_object *meteor1 = create_object(meteor_pos1);
	meteor1->set_texture(meteor_tex_med);
	m_objects.push_back(meteor1);

	point meteor_pos2(WINDOW_WIDTH * 0.4f, WINDOW_HEIGHT * 0.15f);
	game_object *meteor2 = create_object(meteor_pos2);
	meteor2->set_texture(meteor_tex_big);
	m_objects.push_back(meteor2);

	point meteor_pos3(WINDOW_WIDTH * 0.65f, WINDOW_HEIGHT * 0.3f);
	game_object *meteor3 = create_object(meteor_pos3);
	meteor3->set_texture(meteor_tex_big);
	m_objects.push_back(meteor3);

	point meteor_pos4(WINDOW_WIDTH * 0.9f, WINDOW_HEIGHT * 0.25f);
	game_object *meteor4 = create_object(meteor_pos4);
	meteor4->set_texture(meteor_tex_med);
	m_objects.push_back(meteor4);
}

void world_module::update(float delta_time) {
	for (object_storage::const_iterator it = m_objects.cbegin(); it != m_objects.cend(); ++it) {
		(*it)->update(delta_time);
	}
	remove_objects();
}
// TODO: probably only one bullet could reach the edge of the screen
void world_module::remove_objects() {
	
	auto pred = [](game_object *object) {
		return object->to_remove == true;
	};
	object_storage::const_iterator it_end = m_objects.end();
	object_storage::const_iterator it_swap = find_if(m_objects.cbegin(), it_end, pred);
	if (it_swap != it_end) {
		swap(it_swap, it_end);
		delete *it_end;
		m_objects.erase(it_end);
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
	bullet->set_type(object_type::OT_BULLET);
	bullet->move_forward();
	m_objects.push_back(bullet);
}

void world_module::on_notify(game_object *in_object) {
 	spawn_bullet(in_object->get_position());
}
