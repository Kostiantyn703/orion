#ifndef WEAPON_H
#define WEAPON_H

#include "globals.h"

class weapon {
public:
	weapon() : m_position(0.f, 0.f) {}
	~weapon() {}

	bool can_shoot = true;
	float m_reload_timer = 0.f;
	float m_reload_max_time = 300.f;

	void set_postition(const vector2f &in_position)	{	m_position = in_position;	}
	vector2f get_position() const { return m_position; }

private:
	vector2f m_position;

};
#endif // WEAPON_H
