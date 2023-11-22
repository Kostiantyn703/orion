#include "world_module.h"

#include <algorithm>

#include "globals.h"
#include "resource_module.h"
#include <SDL_log.h>

constexpr int OBJECTS_CAPACITY = 20;

world_module::world_module() {
	m_colision_system = std::make_unique<collision_module>();
	m_objects.reserve(OBJECTS_CAPACITY);
}

world_module::~world_module() {
	for (auto it = m_objects.begin(); it != m_objects.end(); ++it) {
		delete *it;
	}
	m_objects.clear();
}

void world_module::init_player(controller *in_controller) {
	vector2f player_pos(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.8f);
	spaceship *player =  create_spaceship(player_pos);
	texture *player_tex = resource_module::get_instance()->get_texture(TEX_NAME_SHIP);
	player->set_texture(player_tex);
	in_controller->set_owner(player);
	player->set_mask(MASK_PLAYER);
	m_objects.push_back(player);
}

//void world_module::init_objects() {
//	texture *meteor_tex_big = resource_module::get_instance()->get_texture(TEX_NAME_METEOR_BROWN_BIG);
//	texture *meteor_tex_med = resource_module::get_instance()->get_texture(TEX_NAME_METEOR_BROWN_MED);
//	
//	vector2f meteor_pos1(WINDOW_WIDTH * 0.15f, WINDOW_HEIGHT * 0.2f);
//	game_object *meteor1 = create_object(meteor_pos1);
//	meteor1->set_texture(meteor_tex_med);
//	meteor1->set_type(object_type::OT_ENEMY);
//	meteor1->set_mask(MASK_ENEMY);
//	m_objects.push_back(meteor1);
//
//	vector2f meteor_pos2(WINDOW_WIDTH * 0.4f, WINDOW_HEIGHT * 0.15f);
//	game_object *meteor2 = create_object(meteor_pos2);
//	meteor2->set_texture(meteor_tex_big);
//	meteor2->set_type(object_type::OT_ENEMY);
//	meteor2->set_mask(MASK_ENEMY);
//	m_objects.push_back(meteor2);
//
//	vector2f meteor_pos3(WINDOW_WIDTH * 0.65f, WINDOW_HEIGHT * 0.3f);
//	game_object *meteor3 = create_object(meteor_pos3);
//	meteor3->set_texture(meteor_tex_big);
//	meteor3->set_type(object_type::OT_ENEMY);
//	meteor3->set_mask(MASK_ENEMY);
//	m_objects.push_back(meteor3);
//
//	vector2f meteor_pos4(WINDOW_WIDTH * 0.9f, WINDOW_HEIGHT * 0.25f);
//	game_object *meteor4 = create_object(meteor_pos4);
//	meteor4->set_texture(meteor_tex_med);
//	meteor4->set_type(object_type::OT_ENEMY);
//	meteor4->set_mask(MASK_ENEMY);
//	m_objects.push_back(meteor4);
//}

void world_module::update(float delta_time) {
	for (object_storage::const_iterator it = m_objects.cbegin(); it != m_objects.cend(); ++it) {
		(*it)->update(delta_time);
		m_colision_system->check_collision(this, *it);
	}
	remove_objects();
}
// TODO: probably only one bullet could reach the edge of the screen
void world_module::remove_objects() {
	auto pred = [](game_object *object) {
		return object->should_remove();
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

game_object *world_module::create_object(vector2f &in_position) const {
	return new game_object(in_position);
}

spaceship *world_module::create_spaceship(vector2f &in_position) const {
	return new spaceship(in_position);
}

void world_module::spawn_bullet(vector2f &in_position) {
	game_object *bullet = create_object(in_position);
	bullet->set_texture(resource_module::get_instance()->get_texture(TEX_NAME_BULLET));
	bullet->set_mask(MASK_PLAYER | MASK_PLAYER_BULLET);
	//bullet->move_forward();
	m_objects.push_back(bullet);
}
// bullet spawner
void world_module::on_notify(vector2f &in_position) {
 	spawn_bullet(in_position);
}
