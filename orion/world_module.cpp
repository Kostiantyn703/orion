#include "world_module.h"

#include <SDL_log.h>
#include <algorithm>
#include <cstdlib>

#include "globals.h"
#include "resource_module.h"
#include <time.h>

constexpr int OBJECTS_CAPACITY = 30;

world_module::world_module() {
	m_colision_system = std::make_unique<collision_module>();

	m_meteor_spawner = std::make_unique<meteor_spawner>();
	m_ship_spawner = std::make_unique<ship_spawner>();

	m_difficulty = std::make_unique<difficulty>();

	m_meteor_spawner->set_listener(this);
	m_ship_spawner->set_listener(this);

	m_objects.reserve(OBJECTS_CAPACITY);

	srand((unsigned int)time(0));

	m_spawn_time = 0.f;
	m_max_spawn_time = SHIP_SPAWN_TIME;

	is_show_title = true;
	is_show_score = false;
	is_game_over = false;

	m_score = 0;
}

world_module::~world_module() {
	clear_objects();
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

	player->set_mask(MASK_PLAYER);
	m_player_pos = player->get_origin_ptr();
	m_objects.push_back(player);
}

void world_module::clear_objects() {
	for (auto it = m_objects.begin(); it != m_objects.end(); ++it) {
		delete *it;
	}
	m_objects.clear();
}

void world_module::update(float delta_time) {
	for (object_storage::iterator it = m_objects.begin(); it != m_objects.end(); ++it) {
		game_object *cur_obj = *it;
		cur_obj->update(delta_time);
		m_colision_system->check_collision(this, cur_obj);
	}
	m_meteor_spawner->update(delta_time);
	if (m_meteor_spawner->spawn_timer_expired()) {
		m_meteor_spawner->reload_timer();
		m_meteor_spawner->set_spawn_pos(m_player_pos->get_x());
		m_meteor_spawner->notify();
	}

	m_spawn_time -= delta_time;
	if (m_spawn_time < 0.f) {
		size_t idx = calculate_idx(m_block_data.size());
		if (!m_block_data.empty()) {
			m_ship_spawner->notify_spawn(m_block_data[idx % m_block_data.size()]);
			m_spawn_time = m_max_spawn_time;
		}
	}

	remove_objects();
	handle_difficulty(m_score);
}

void world_module::remove_objects() {
	// only one object per frame set to remove
	object_storage::iterator left_bound = m_objects.begin();
	object_storage::iterator right_bound = m_objects.end();
	while (left_bound != right_bound) {
		if ((*left_bound)->should_remove()) {
			--right_bound;
			std::iter_swap(left_bound, right_bound);
			continue;
		}
		++left_bound;
	}
	auto pred = [](game_object *object) {
		return object->should_remove();
	};
	object_storage::iterator it = find_if(m_objects.begin(), m_objects.end(), pred);
	if (it != m_objects.end()) {
		delete *it;
		m_objects.erase(it, m_objects.end());
	}
}

bullet *world_module::spawn_bullet(const vector2f &in_position, const vector2f &in_forward_vector, const float in_velocity) const {
	return new bullet(in_position, in_forward_vector, in_velocity);
}

// bullet spawner
void world_module::on_notify(const vector2f &in_position, const vector2f &in_forward_vector, int in_type) {
	bool is_enemy = (in_type == 1);
	texture *tex = resource_module::get_instance()->get_texture(in_type == 0 ? TEX_NAME_BULLET_GREEN : TEX_NAME_BULLET_RED);
	
	vector2f pos = in_position;
	pos.set_x(pos.get_x() - tex->get_width() * 0.5f);

 	bullet *bul = spawn_bullet(pos, in_forward_vector, is_enemy ? ENEMY_BULLET_VELOCITY : PLAYER_BULLET_VELOCITY);
	bul->set_texture(tex);
	bul->set_mask(!is_enemy ? (MASK_PLAYER | MASK_PLAYER_BULLET | MASK_ENEMY_BULLET) : (MASK_ENEMY | MASK_ENEMY_BULLET | MASK_PLAYER_BULLET));
	if (is_enemy) {
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

void world_module::handle_difficulty(const size_t &in_cur_score) {
	bool should_increase = in_cur_score > m_difficulty->m_cur_level * DIFFICULTY_STEP;
	if (should_increase) {
		++m_difficulty->m_cur_level;
		on_difficulty_changed();
	}
}

void world_module::on_difficulty_changed() {
	m_max_spawn_time -= SHIP_SPAWN_TIME_STEP;
	if (m_max_spawn_time < SHIP_MIN_SPAWN_TIME) {
		m_max_spawn_time = SHIP_MIN_SPAWN_TIME;
	}
	float meteor_velocity = m_meteor_spawner->get_velocity();
	meteor_velocity += METEOR_VELOCITY_STEP;
	m_meteor_spawner->set_velocity(meteor_velocity);
}
