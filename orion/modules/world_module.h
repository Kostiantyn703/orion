#ifndef WORLD_MODULE_H
#define WORLD_MODULE_H

#include <vector>
#include <memory>

#include "../objects/game_object.h"
#include "../objects/spaceship.h"
#include "../objects/bullet.h"
#include "../objects/meteor.h"

#include "../interfaces/subscriber.h"
#include "../input/controller.h"

#include "../gameplay/meteor_spawner.h"
#include "../gameplay/ship_spawner.h"
#include "../gameplay/game_block.h"

#include "collision_module.h"

using object_storage = std::vector<game_object*>;

class difficulty_data {
public:
	difficulty_data() : level(1) {}

	size_t level;
};

class world_module : public subscriber {
public:
	world_module();
	virtual ~world_module();

	void update(float delta_time);
	void remove_objects();
	
	void set_show_title(bool val) { show_title = val; }
	bool should_show_title() const { return show_title; }

	void set_show_score(bool val) { show_score = val; }
	bool get_show_score() const { return show_score; }

	void set_game_over(bool val) { game_over = val; }
	bool get_game_over() const { return game_over; }

	void reset_score() { score = 0; }
	size_t get_score() const { return score; }

	void reset_difficulty() { difficulty->level = 1; }

	void init_player(input_controller *controller);
	void clear_objects();

	bullet *create_bullet(const vector2f &position, const vector2f &forward_vector) const;

	virtual void on_notify(const vector2f &position, const vector2f &forward_vector, int type_val) override;
	virtual void on_notify(game_object &object) override;

	void add_score(const size_t &val) { score += val; }

	void set_max_spawn_time(float val) { max_spawn_time = val; }

	object_storage objects;
	std::vector<game_block> game_blocks;

private:
	bool show_title;
	bool show_score;
	bool game_over;

	float spawn_time;
	float max_spawn_time;

	size_t score;

	std::unique_ptr<difficulty_data> difficulty;

	std::unique_ptr<collision_module> colision_system;

	std::unique_ptr<meteor_spawner> meteor_spawner_instance;
	std::unique_ptr<ship_spawner>	ship_spawner_instance;

	vector2f *player_pos = nullptr;

	size_t calculate_idx(size_t val);

	void handle_difficulty(const size_t &score);
	void on_difficulty_changed();
};
#endif // WORLD_MODULE_H
