#include "spaceship.h"

spaceship::spaceship(vector2f &initial_point)
	:	game_object(initial_point)
{
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
	game_object::update(delta_time);
	if (!m_weapon->can_shoot) {
		m_weapon->m_reload_timer -= delta_time;
		if (m_weapon->m_reload_timer < 0.f) {
			m_weapon->can_shoot = true;
		}
	}
}


void spaceship::shoot() {
	if (m_weapon->can_shoot) {
		vector2f spawn_pos = get_origin() + m_weapon->get_position();
		//m_listener->on_notify(spawn_pos);
		m_weapon->can_shoot = false;
		m_weapon->m_reload_timer = m_weapon->m_reload_max_time;
	}
}