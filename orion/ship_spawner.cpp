#include "ship_spawner.h"

#include "spaceship.h"
#include "resource_module.h"
#include "game_block.h"
#include "behavior.h"

std::map<std::string, action_type> g_actions_map = {
	{	"forward"	,	action_type::AT_MOVE_FORWARD	},
	{	"backward"	,	action_type::AT_MOVE_BACKWARDS	},
	{	"left"		,	action_type::AT_MOVE_LEFT		},
	{	"right"		,	action_type::AT_MOVE_RIGHT		}
};

std::map<std::string, condition_type> g_cond_map = {
	{	"x_pos"		,	condition_type::CT_POSITION_X	},
	{	"y_pos"		,	condition_type::CT_POSITION_Y	}
};

void ship_spawner::notify_spawn(const game_block &in_block) {
	int idx = std::rand() % int(in_block.m_items.size());
	const behavior_item &beh_item = in_block.m_items[idx];
	float spawn_coord = beh_item.m_spawn_range.is_valid() ? calculate_coordinate(beh_item.m_spawn_range) : beh_item.m_spawn_pos;
	vector2f spawn_pos = vector2f(WINDOW_WIDTH * spawn_coord, -OUT_OFFSET);
	
	std::string tex_name;
	if (in_block.m_type == 0) tex_name = TEX_NAME_ENEMY_00;
	if (in_block.m_type == 1) tex_name = TEX_NAME_ENEMY_01;
	if (in_block.m_type == 2) tex_name = TEX_NAME_ENEMY_02;
	texture *cur_tex = resource_module::get_instance()->get_texture(tex_name);

	vector2f forward_vec(0.f, 1.f);
	spaceship *enemy = spawn_spaceship(spawn_pos, forward_vec);
	enemy->set_texture(cur_tex);
	enemy->set_listener(m_world);
	enemy->on_spawn(in_block.is_shooter);

	set_behavior(*enemy, beh_item);
	enemy->get_behavior()->init();

	m_world->on_notify(*enemy);
}

void ship_spawner::set_behavior(spaceship &in_ship, const behavior_item &in_item) {
	for (std::vector<behavior_data>::const_iterator it = in_item.m_behavior_data.begin(); it != in_item.m_behavior_data.end(); ++it) {
		action act;
		auto act_it = g_actions_map.find(it->m_action_name);
		if (act_it != g_actions_map.end()) {
			act.set_type(act_it->second);
		}
		if (!it->m_condition_name.empty()) {
			auto cond_it = g_cond_map.find(it->m_condition_name);
			end_condition cond;
			cond.set_type(cond_it->second);
			float coord_data = 0.f;
			float cond_data = it->m_range.is_valid() ? calculate_coordinate(it->m_range) : it->m_condition_data;
			if (cond.get_type() == condition_type::CT_POSITION_X) {
				coord_data = WINDOW_WIDTH * cond_data;
			} else {
				coord_data = WINDOW_HEIGHT * cond_data;
			}
			cond.set_data(coord_data);
			act.set_condition(cond);
		}
		in_ship.get_behavior()->add_action(act);
	}
}

game_object *ship_spawner::spawn_object(const vector2f &in_position, const vector2f &in_forward_vector) const {
	return new spaceship(in_position, in_forward_vector);
}

spaceship *ship_spawner::spawn_spaceship(const vector2f &in_position, const vector2f &in_forward_vector) const {
	return new spaceship(in_position, in_forward_vector);
}

float ship_spawner::calculate_coordinate(const range &in_range) {
	int diff = in_range.m_max - in_range.m_min;
	int result = in_range.m_min + (std::rand() % diff);

	return result / 100.f;
}