#include "spaceship.h"
#include "world_module.h"

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
}

void spaceship::update(float delta_time) {
	// duplicate at least in bullet::update
	vector2f delta_vec = get_move_dir() * get_velocity() * delta_time;
	set_origin(get_origin() + delta_vec);
	m_aabb.calculate(get_origin(), get_size());
	
	if (m_weapon && !m_weapon->can_shoot()) {
		m_weapon->m_reload_timer -= delta_time;
		if (m_weapon->m_reload_timer < 0.f) {
			m_weapon->set_can_shoot(true);
		}
	}
	set_move_dir(vector2f(0.f, 0.f));
}

void spaceship::move_forward() {
	vector2f dir = get_forward_vector();
	merge_movement(dir);
}

void spaceship::move_right() {
	vector2f dir = get_forward_vector().get_swapped().get_inverse();
	merge_movement(dir);
}

void spaceship::move_backward() {
	vector2f dir = get_forward_vector().get_inverse();
	merge_movement(dir);
}

void spaceship::move_left() {
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