#include "spaceship.h"

spaceship::spaceship(vector2f &initial_point, vector2f &in_forward_vector)
	:	game_object(initial_point)
{
	set_forward_vector(in_forward_vector);
	m_weapon = new weapon();
	vector2f wep_pos(get_size().get_x() * 0.5f, 0.f);
	m_weapon->set_postition(wep_pos);
}

spaceship::spaceship(float initial_x, float initial_y)
	:	game_object(initial_x, initial_y)
{
	m_weapon = new weapon();
	vector2f wep_pos(get_size().get_x() * 0.5f, 0.f);
	m_weapon->set_postition(wep_pos);
}

spaceship::~spaceship() {
	delete m_weapon;
}

void spaceship::update(float delta_time) {
	vector2f delta_vec = get_move_dir() * delta_time;
	set_origin(get_origin() + delta_vec);
	m_aabb.calculate(get_origin(), get_size());
	
	if (!m_weapon->can_shoot) {
		m_weapon->m_reload_timer -= delta_time;
		if (m_weapon->m_reload_timer < 0.f) {
			m_weapon->can_shoot = true;
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
	if (m_weapon->can_shoot) {
		vector2f spawn_pos = get_origin() + m_weapon->get_position();
		//m_listener->on_notify(spawn_pos);
		m_weapon->can_shoot = false;
		m_weapon->m_reload_timer = m_weapon->m_reload_max_time;
	}
}