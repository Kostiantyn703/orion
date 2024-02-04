#include "world_module.h"

#include <SDL_log.h>
#include <algorithm>
#include <cstdlib>

#include "globals.h"
#include "resource_module.h"
#include <time.h>

constexpr int OBJECTS_CAPACITY = 20;

world_module::world_module() {

	m_colision_system = std::make_unique<collision_module>();

	m_meteor_spawner = std::make_unique<meteor_spawner>();
	m_ship_spawner = std::make_unique<ship_spawner>();

	m_meteor_spawner->set_listener(this);
	m_ship_spawner->set_listener(this);

	m_objects.reserve(OBJECTS_CAPACITY);

	srand(time(0));
}

world_module::~world_module() {
	for (auto it = m_objects.begin(); it != m_objects.end(); ++it) {
		delete *it;
	}
	m_objects.clear();
	SDL_Log("Your score %d", m_score);
}

void world_module::init() {}

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
	m_player_pos = player->get_origin_ptr();
	m_objects.push_back(player);
}

void world_module::update(float delta_time) {
	for (object_storage::const_iterator it = m_objects.cbegin(); it != m_objects.cend(); ++it) {
		(*it)->update(delta_time);
		m_colision_system->check_collision(this, *it);
	}
	m_meteor_spawner->update(delta_time);
	if (m_meteor_spawner->spawn_timer_expired()) {
		m_meteor_spawner->reload_timer();
		m_meteor_spawner->set_spawn_pos(m_player_pos->get_x());
		m_meteor_spawner->notify();
	}

	m_spawn_time -= delta_time;
	if (m_spawn_time < 0.f) {
		//size_t idx = calculate_idx(m_block_data.size());
		m_ship_spawner->notify_spawn(m_block_data[block_idx % m_block_data.size()]);
		m_spawn_time = m_max_spawn_time;
		++block_idx;
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
		delete *it_end;
		m_objects.erase(it_end);
	}
}

bullet *world_module::spawn_bullet(const vector2f &in_position, const vector2f &in_forward_vector) const {
	return new bullet(in_position, in_forward_vector);
}

// bullet spawner
void world_module::on_notify(const vector2f &in_position, const vector2f &in_forward_vector, int in_type) {
	texture *tex = resource_module::get_instance()->get_texture(in_type == 0 ? TEX_NAME_BULLET_GREEN : TEX_NAME_BULLET_RED);
	
	vector2f pos = in_position;
	pos.set_x(pos.get_x() - tex->get_width() * 0.5f);

 	bullet *bul = spawn_bullet(pos, in_forward_vector);
	bul->set_texture(tex);
	bul->set_mask(in_type == 0 ? (MASK_PLAYER | MASK_PLAYER_BULLET | MASK_ENEMY_BULLET) : (MASK_ENEMY | MASK_ENEMY_BULLET | MASK_PLAYER_BULLET));
	if (in_type == 1) {
		bul->set_rotation(180.f);
	}
	m_objects.push_back(bul);
}
// meteor spawner
void world_module::on_notify(game_object &in_object) {
	m_objects.push_back(&in_object);
}

size_t world_module::calculate_idx(size_t in_val) {
	return std::rand() % int(in_val);
}
