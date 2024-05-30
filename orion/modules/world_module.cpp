#include "world_module.h"

#include <time.h>
#include <algorithm>
#include <cstdlib>

#include <SDL_log.h>

#include "../utils/globals.h"

#include "resource_module.h"

constexpr int OBJECTS_CAPACITY = 30;

world_module::world_module() : spawn_time(0.f), max_spawn_time(SHIP_SPAWN_TIME), score(0),
								show_title(true), show_score(false), game_over(false)
{
	colision_system = std::make_unique<collision_module>();

	meteor_spawner_instance = std::make_unique<meteor_spawner>();
	ship_spawner_instance = std::make_unique<ship_spawner>();

	difficulty = std::make_unique<difficulty_data>();

	meteor_spawner_instance->set_listener(this);
	ship_spawner_instance->set_listener(this);

	objects.reserve(OBJECTS_CAPACITY);

	srand((unsigned int)time(0));
}

world_module::~world_module() {
	clear_objects();
}

void world_module::init_player(input_controller *controller) {
	vector2f pos(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.8f);
	vector2f forward_vec(0.f, -1.f);
	spaceship *player = ship_spawner_instance->spawn_spaceship(pos, forward_vec);
	texture *player_tex = resource_module::get_instance()->get_texture(TEX_NAME_SHIP);
	player->set_texture(player_tex);
	player->init();
	controller->set_owner(player);
	player->set_listener(this);

	player->set_mask(MASK_PLAYER);
	player_pos = player->get_origin_ptr();
	objects.push_back(player);
}

void world_module::clear_objects() {
	for (object_storage::iterator it = objects.begin(); it != objects.end(); ++it) {
		delete *it;
	}
	objects.clear();
}

void world_module::update(float delta_time) {
	for (object_storage::iterator it = objects.begin(); it != objects.end(); ++it) {
		game_object *obj = *it;
		obj->update(delta_time);
		colision_system->check_collision(this, obj);
	}
	meteor_spawner_instance->update(delta_time);
	if (meteor_spawner_instance->spawn_timer_expired()) {
		meteor_spawner_instance->spawn(player_pos->get_x());
	}

	spawn_time -= delta_time;
	if (spawn_time < 0.f) {
		size_t idx = calculate_idx(game_blocks.size());
		if (!game_blocks.empty()) {
			ship_spawner_instance->notify_spawn(game_blocks[idx % game_blocks.size()]);
			spawn_time = max_spawn_time;
		}
	}

	remove_objects();
	handle_difficulty(score);
}

void world_module::remove_objects() {
	object_storage::iterator left_bound = objects.begin();
	object_storage::iterator right_bound = objects.end();
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
	object_storage::iterator it = find_if(objects.begin(), objects.end(), pred);
	if (it != objects.end()) {
		delete *it;
		objects.erase(it, objects.end());
	}
}

bullet *world_module::create_bullet(const vector2f &position, const vector2f &forward_vector) const {
	return new bullet(position, forward_vector, BULLET_VELOCITY);
}

// bullet spawner
void world_module::on_notify(const vector2f &position, const vector2f &forward_vector, int type) {
	bool is_enemy = (type == 1);
	texture *tex = resource_module::get_instance()->get_texture(type == 0 ? TEX_NAME_BULLET_GREEN : TEX_NAME_BULLET_RED);
	
	float spawn_x = position.get_x() - tex->get_width() * 0.5f;
	float spawn_y = position.get_y();

 	bullet *bul = create_bullet(vector2f(spawn_x, spawn_y), forward_vector);
	bul->set_texture(tex);
	bul->set_mask(!is_enemy ? (MASK_PLAYER | MASK_PLAYER_BULLET | MASK_ENEMY_BULLET) : (MASK_ENEMY | MASK_ENEMY_BULLET | MASK_PLAYER_BULLET));
	if (is_enemy) {
		bul->set_rotation(180.f);
	}
	objects.push_back(bul);
}
// meteor spawner
void world_module::on_notify(game_object &object) {
	objects.push_back(&object);
}

size_t world_module::calculate_idx(size_t val) {
	return std::rand() % int(val);
}

void world_module::handle_difficulty(const size_t &score) {
	bool should_increase = score > difficulty->level * DIFFICULTY_STEP;
	if (should_increase) {
		++difficulty->level;
		on_difficulty_changed();
	}
}

void world_module::on_difficulty_changed() {
	max_spawn_time -= SHIP_SPAWN_TIME_STEP;
	if (max_spawn_time < SHIP_MIN_SPAWN_TIME) {
		max_spawn_time = SHIP_MIN_SPAWN_TIME;
	}
	float meteor_velocity = meteor_spawner_instance->get_velocity();
	meteor_velocity += METEOR_VELOCITY_STEP;
	meteor_spawner_instance->set_velocity(meteor_velocity);
}
