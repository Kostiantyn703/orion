#include "spaceship.h"

#include <SDL_log.h>

#include "../modules/world_module.h"
#include "../utils/globals.h"

spaceship::spaceship(const vector2f &initial_point, const vector2f &forward_vector)
	:	game_object(initial_point)
{
	set_forward_vector(forward_vector);
	set_velocity(SPACESHIP_VELOCITY);
}

spaceship::~spaceship() {
	delete gun;
}

void spaceship::init() {
	init_weapon();
	type = ship_type::ST_PLAYER;
	calculate_origin();
}

void spaceship::on_spawn(bool is_shooter) {
	type = ship_type::ST_ENEMY;
	if (is_shooter)
		init_weapon();

	calculate_origin();
	behavior_instance = std::make_unique<behavior>();
	set_mask(MASK_ENEMY);
	set_score_value(SPACESHIP_SCORE);
}

bool spaceship::on_intersect() {
	set_to_remove(true);
	if (type == ship_type::ST_PLAYER)
		return true;

	return false;
}

void spaceship::update(float delta_time) {
	if (type == ship_type::ST_ENEMY)
		behavior_instance->update(delta_time, *this);

	game_object::update(delta_time);

	if (gun && !gun->get_can_shoot()) {
		gun->decrease_reload_timer(delta_time);
		if (gun->get_reload_timer() < 0.f)
			gun->set_can_shoot(true);
	}
	reset_movement();

	if (type == ship_type::ST_ENEMY) {
		if (get_origin().get_y() > WINDOW_HEIGHT + OUT_OFFSET) {
			set_to_remove(true);
		}
	}
}

void spaceship::move_forward() {
	if (blocked_up)
		return;

	vector2f dir = get_forward_vector();
	merge_movement(dir);
}

void spaceship::move_right() {
	if (blocked_right)
		return;
	
	vector2f dir = get_forward_vector().get_swapped().get_inverse();
	merge_movement(dir);
}

void spaceship::move_backward() {
	if (blocked_down)
		return;

	vector2f dir = get_forward_vector().get_inverse();
	merge_movement(dir);
}

void spaceship::move_left() {
	if (blocked_left)
		return;

	vector2f dir = get_forward_vector().get_swapped();
	merge_movement(dir);
}

void spaceship::shoot() {
	if (gun->get_can_shoot()) {
		vector2f spawn_pos = get_origin() + gun->get_position();
		world->on_notify(spawn_pos, get_forward_vector(), type);
		gun->set_can_shoot(false);
		gun->reset_reload_timer();
	}
}

void spaceship::borders_intersect(border_side side) {
	switch (side) {
	case border_side::BS_NORTH:
		blocked_up = true;
		break;
	case border_side::BS_EAST:
		blocked_right = true;
		break;
	case border_side::BS_SOUTH:
		blocked_down = true;
		break;
	case border_side::BS_WEST:
		blocked_left = true;
		break;
	}
}

void spaceship::reset_movement() {
	set_direction	(vector2f(0.f, 0.f));
	blocked_up		= false;
	blocked_right	= false;
	blocked_down	= false;
	blocked_left	= false;
}

void spaceship::init_weapon() {
	gun = new weapon();
	vector2f pos(get_size().get_x() * 0.5f, 0.f);
	gun->set_postition(pos);
	gun->reset_reload_timer();
}
