#include "game_object.h"

#include <SDL_log.h>

game_object::game_object(point &initial_point) {
	set_position(initial_point.x_pos, initial_point.y_pos);
}

game_object::game_object(float initial_x, float initial_y) {
	set_position(initial_x, initial_y);
}

game_object::~game_object() {}

void game_object::update(float delta_time) {
	point curr_pos = get_position();
	point curr_dir = get_direction();

	curr_pos.x_pos += curr_dir.x_pos * delta_time * m_velocity;
	curr_pos.y_pos += curr_dir.y_pos * delta_time * m_velocity;

	set_position(curr_pos.x_pos, curr_pos.y_pos);
}

void game_object::set_position(float in_x, float in_y) {
	m_position.x_pos = in_x;
	m_position.y_pos = in_y; 
}

point game_object::get_direction() const {
	point result(0.f, 0.f);
	switch (m_direction) {
		case direction::D_UP:
			result.y_pos = -1.f;
		break;
		case direction::D_RIGHT:
			result.x_pos = 1.f;
		break;
		case direction::D_DOWN:
			result.y_pos = 1.f;
		break;
		case direction::D_LEFT:
			result.x_pos = -1.f;
		break;
	}
	return result;
}
