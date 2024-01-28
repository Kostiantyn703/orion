#include "world_module.h"

#include <SDL_log.h>
#include <algorithm>

#include "globals.h"
#include "resource_module.h"

constexpr int OBJECTS_CAPACITY = 20;

world_module::world_module() {

	m_colision_system = std::make_unique<collision_module>();

	m_meteor_spawner = std::make_unique<meteor_spawner>();
	m_ship_spawner = std::make_unique<ship_spawner>();

	m_meteor_spawner->set_listener(this);
	m_ship_spawner->set_listener(this);

	m_objects.reserve(OBJECTS_CAPACITY);

	m_reload_time = m_max_reload_time;
}

world_module::~world_module() {
	for (auto it = m_objects.begin(); it != m_objects.end(); ++it) {
		delete *it;
	}
	m_objects.clear();
}

void world_module::init() {

}

void world_module::init_player(controller *in_controller) {
	vector2f player_pos(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.8f);
	vector2f forward_vec(0.f, -1.f);
	spaceship *player = m_ship_spawner->spawn_spaceship(player_pos, forward_vec);
	texture *player_tex = resource_module::get_instance()->get_texture(TEX_NAME_SHIP);
	player->set_texture(player_tex);
	player->init();
	in_controller->set_owner(player);
	player->set_listener(this);
	// TODO: temporary god mod to prevent hit by enemy during test
	player->set_mask(MASK_PLAYER | MASK_ENEMY);
	m_objects.push_back(player);
}

void world_module::update(float delta_time) {
	for (object_storage::const_iterator it = m_objects.cbegin(); it != m_objects.cend(); ++it) {
		(*it)->update(delta_time);
		m_colision_system->check_collision(this, *it);
	}
	//m_meteor_spawner->update(delta_time);

	if (!m_script_playing) {
		m_reload_time -= delta_time;
		if (m_reload_time < 0.f) {
			m_ship_spawner->notify_spawn(m_block_data[cur_block_idx % m_block_data.size()]);
			m_script_playing = true;
			++cur_block_idx;
			m_reload_time = m_max_reload_time;
		}
	}
	remove_objects();
}

void world_module::remove_objects() {
	auto pred = [](game_object *object) {
		return object->should_remove();
	};
	object_storage::const_iterator it_end = m_objects.end();
	object_storage::const_iterator it_swap = find_if(m_objects.cbegin(), it_end, pred);
	if (it_swap != it_end) {
		swap(it_swap, it_end);
 		(*it_end)->on_remove(m_script_playing);
		delete *it_end;
		m_objects.erase(it_end);
	}
}

bullet *world_module::spawn_bullet(const vector2f &in_position, const vector2f &in_forward_vector) const {
	return new bullet(in_position, in_forward_vector);
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
// meteor spawner
void world_module::on_notify(game_object &in_object) {
	m_objects.push_back(&in_object);
}
