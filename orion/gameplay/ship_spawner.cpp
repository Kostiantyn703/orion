#include "ship_spawner.h"

#include "../modules/resource_module.h"
#include "../objects/spaceship.h"

#include "game_block.h"
#include "behavior.h"

std::map<std::string, action_type> actions_map = {
	{ ACTION_FORWARD	,	action_type::AT_MOVE_FORWARD	},
	{ ACTION_BACKWARD	,	action_type::AT_MOVE_BACKWARD	},
	{ ACTION_LEFT		,	action_type::AT_MOVE_LEFT		},
	{ ACTION_RIGHT		,	action_type::AT_MOVE_RIGHT		}
};

std::map<std::string, condition_type> conditions_map = {
	{	X_POS		,	condition_type::CT_POSITION_X	},
	{	Y_POS		,	condition_type::CT_POSITION_Y	}
};

void ship_spawner::notify_spawn(const game_block &block) {
	int idx = std::rand() % int(block.items.size());
	const behavior_item &beh_item = block.items[idx];
	float spawn_coord = beh_item.spawn_range.is_valid() ? calculate_coordinate(beh_item.spawn_range) : beh_item.spawn_pos_x;
	vector2f spawn_pos = vector2f(WINDOW_WIDTH * spawn_coord, -OUT_OFFSET);
	
	std::string tex_name;
	if (block.type == 0) tex_name = TEX_NAME_ENEMY_00;
	if (block.type == 1) tex_name = TEX_NAME_ENEMY_01;
	if (block.type == 2) tex_name = TEX_NAME_ENEMY_02;
	texture *tex = resource_module::get_instance()->get_texture(tex_name);

	vector2f forward_vec(0.f, 1.f);
	spaceship *enemy = spawn_spaceship(spawn_pos, forward_vec);
	enemy->set_texture(tex);
	enemy->set_listener(world);
	enemy->on_spawn(block.is_shooter);

	set_behavior(*enemy, beh_item);
	enemy->get_behavior()->init();

	world->on_notify(*enemy);
}

void ship_spawner::set_behavior(spaceship &ship, const behavior_item &item) {
	for (std::vector<behavior_data>::const_iterator it = item.behavior.begin(); it != item.behavior.end(); ++it) {
		action act;
		auto act_it = actions_map.find(it->action_name);
		if (act_it != actions_map.end()) {
			act.set_type(act_it->second);
		}
		if (!it->condition_name.empty()) {
			auto cond_it = conditions_map.find(it->condition_name);
			end_condition cond;
			cond.set_type(cond_it->second);
			float coordinate = 0.f;
			float condition = it->range.is_valid() ? calculate_coordinate(it->range) : it->condition_data;
			if (cond.get_type() == condition_type::CT_POSITION_X) {
				coordinate = WINDOW_WIDTH * condition;
			} else {
				coordinate = WINDOW_HEIGHT * condition;
			}
			cond.set_data(coordinate);
			act.set_condition(cond);
		}
		ship.get_behavior()->add_action(act);
	}
}

spaceship *ship_spawner::spawn_spaceship(const vector2f &position, const vector2f &forward_vector) const {
	return new spaceship(position, forward_vector);
}

float ship_spawner::calculate_coordinate(const range_container &range) {
	int diff = range.max - range.min;
	int result = range.min + (std::rand() % diff);

	return result / 100.f;
}