#include "world_module.h"
#include <SDL_log.h>
#include <algorithm>

#include "globals.h"
#include "resource_module.h"

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
	vector2f forward_vec(0.f, -1.f);
	spaceship *player =  spawn_spaceship(player_pos, forward_vec);
	texture *player_tex = resource_module::get_instance()->get_texture(TEX_NAME_SHIP);
	player->set_texture(player_tex);
	player->init();
	in_controller->set_owner(player);
	player->set_listener(this);
	// TODO: temporary god mod to prevent hit by enemy during test
	player->set_mask(MASK_PLAYER | MASK_ENEMY);
	m_objects.push_back(player);
}

void world_module::init_objects() {
	texture *meteor_tex_big = resource_module::get_instance()->get_texture(TEX_NAME_METEOR_BROWN_BIG);
	texture *meteor_tex_med = resource_module::get_instance()->get_texture(TEX_NAME_METEOR_BROWN_MED);
	
	vector2f met_forward_vec(0.f, 1.f);
	vector2f met_pos(WINDOW_WIDTH * 0.15f, WINDOW_HEIGHT * 0.2f);
	meteor *met = spawn_meteor(met_pos, met_forward_vec);
	met->set_texture(meteor_tex_big);
	met->set_mask(MASK_ENEMY);
	m_objects.push_back(met);

	vector2f met_pos2(WINDOW_WIDTH * 0.4f, WINDOW_HEIGHT * 0.15f);
	meteor *met2 = spawn_meteor(met_pos2, met_forward_vec);
	met2->set_texture(meteor_tex_big);
	met2->set_mask(MASK_ENEMY);
	m_objects.push_back(met2);
	//vector2f meteor_pos3(WINDOW_WIDTH * 0.65f, WINDOW_HEIGHT * 0.3f);
	//vector2f meteor_pos4(WINDOW_WIDTH * 0.9f, WINDOW_HEIGHT * 0.25f);
}

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

game_object *world_module::create_object(vector2f &in_position) const {
	return new game_object(in_position);
}

spaceship *world_module::spawn_spaceship(vector2f &in_position, vector2f &in_forward_vector) const {
	return new spaceship(in_position, in_forward_vector);
}

bullet *world_module::spawn_bullet(const vector2f &in_position, const vector2f &in_forward_vector) const {
	return new bullet(in_position, in_forward_vector);
}

meteor *world_module::spawn_meteor(const vector2f &in_position, const vector2f &in_forward_vector) const {
	return new meteor(in_position, in_forward_vector);
}
// bullet spawner
void world_module::on_notify(const vector2f &in_position, const vector2f &in_forward_vector) {
	texture *tex = resource_module::get_instance()->get_texture(TEX_NAME_BULLET);
	
	vector2f pos = in_position;
	pos.set_x(pos.get_x() - tex->get_width() * 0.5f);

 	bullet *bul = spawn_bullet(pos, in_forward_vector);
	bul->set_texture(tex);
	bul->set_mask(MASK_PLAYER | MASK_PLAYER_BULLET);
	m_objects.push_back(bul);
}
