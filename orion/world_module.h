#ifndef WORLD_MODULE_H
#define WORLD_MODULE_H

#include <vector>
#include <memory>

#include "game_object.h"
#include "controller.h"
#include "subscriber.h"
#include "collision_module.h"

#include "spaceship.h"
#include "bullet.h"
#include "meteor.h"
#include "meteor_spawner.h"
#include "ship_spawner.h"
#include "game_block.h"

using object_storage = std::vector<game_object*>;

class difficulty {
public:
	difficulty() : m_cur_level(1) {}
	
	size_t m_cur_level;
};

class world_module : public subscriber {
public:
	world_module();
	virtual ~world_module();

	void init();

	void update(float delta_time);
	void remove_objects();
	
	void init_player(controller *in_controller);
	void clear_objects();

	bullet *spawn_bullet(const vector2f &in_position, const vector2f &in_forward_vector, const float in_velocity) const;

	virtual void on_notify(const vector2f &in_position, const vector2f &in_forward_vector, int in_type) override;
	virtual void on_notify(game_object &in_object) override;

	void add_score(const size_t &in_val) { m_score += in_val; }

	void set_max_spawn_time(float in_val) { m_max_spawn_time = in_val; }

	object_storage				m_objects;
	std::vector<game_block>		m_block_data;

	size_t block_idx = 0;

	bool show_title = true;
private:
	float m_spawn_time = 0.f;
	float m_max_spawn_time = 0.f;

	size_t m_score = 0;

	std::unique_ptr<difficulty> m_difficulty;

	std::unique_ptr<collision_module> m_colision_system;

	std::unique_ptr<meteor_spawner> m_meteor_spawner;
	std::unique_ptr<ship_spawner>	m_ship_spawner;

	vector2f *m_player_pos = nullptr;

	size_t calculate_idx(size_t in_val);

	void handle_difficulty(const size_t &in_cur_score);
	void on_difficulty_changed();
};
#endif // WORLD_MODULE_H
