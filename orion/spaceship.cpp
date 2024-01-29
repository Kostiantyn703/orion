#include "spaceship.h"
#include "world_module.h"
#include "globals.h"

spaceship::spaceship(const vector2f &initial_point, const vector2f &in_forward_vector)
	:	game_object(initial_point)
{
	set_forward_vector(in_forward_vector);
	set_velocity(PLAYER_VELOCITY);
}

spaceship::spaceship(const vector2f &initial_point, const vector2f &in_forward_vector, float in_velocity)
	:	game_object(initial_point)
{
	set_forward_vector(in_forward_vector);
	set_velocity(in_velocity);
}

spaceship::~spaceship() {
	delete m_weapon;
}

void spaceship::init() {
	m_weapon = new weapon();
	vector2f wep_pos(get_size().get_x() * 0.5f, 0.f);
	m_weapon->set_postition(wep_pos);
	m_type = ship_type::ST_PLAYER;
	recalc_pos();
}
// TODO: temporary
void spaceship::on_spawn() {
	recalc_pos();
	m_type = ship_type::ST_ENEMY;
	m_behavior = std::make_unique<behavior>();
	set_mask(MASK_ENEMY);
}

void spaceship::on_remove(bool &in_val) {
	in_val = false;
}

void spaceship::update(float delta_time) {
	if (m_type == ship_type::ST_ENEMY) {
		m_behavior->update(delta_time, *this);
	}

	game_object::update(delta_time);

	if (m_weapon && !m_weapon->can_shoot()) {
		m_weapon->m_reload_timer -= delta_time;
		if (m_weapon->m_reload_timer < 0.f) {
			m_weapon->set_can_shoot(true);
		}
	}
	reset_movement();

	if (m_type == ship_type::ST_ENEMY) {
		if (get_origin().get_y() > WINDOW_HEIGHT + OUT_OFFSET) {
			set_to_remove(true);
		}
	}
}

void spaceship::move_forward() {
	if (blocked_up) return;
	vector2f dir = get_forward_vector();
	merge_movement(dir);
}

void spaceship::move_right() {
	if (blocked_right) return;
	vector2f dir = get_forward_vector().get_swapped().get_inverse();
	merge_movement(dir);
}

void spaceship::move_backward() {
	if (blocked_down) return;
	vector2f dir = get_forward_vector().get_inverse();
	merge_movement(dir);
}

void spaceship::move_left() {
	if (blocked_left) return;
	vector2f dir = get_forward_vector().get_swapped();
	merge_movement(dir);
}

void spaceship::shoot() {
	if (m_weapon->can_shoot()) {
		vector2f spawn_pos = get_origin() + m_weapon->get_position();
		m_listener->on_notify(spawn_pos, get_forward_vector());
		m_weapon->set_can_shoot(false);
		m_weapon->reset_reload_timer();
	}
}

void spaceship::borders_intersect(border_side in_side) {
	switch (in_side) {
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
	set_move_dir	(vector2f(0.f, 0.f));
	blocked_up		= false;
	blocked_right	= false;
	blocked_down	= false;
	blocked_left	= false;
}
