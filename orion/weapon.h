#ifndef WEAPON_H
#define WEAPON_H

#include "globals.h"

class weapon {
public:
	weapon() : m_can_shoot(true), m_reload_timer(0.f), m_position(0.f, 0.f) {}
	~weapon() {}

	void	set_can_shoot	(bool val)	{	m_can_shoot = val;		}
	float	can_shoot		()	const	{	return m_can_shoot;		}

	void		set_postition	(const vector2f &in_position)	{	m_position = in_position;	}
	vector2f	get_position	()	const						{	return m_position;			}

	float	m_reload_timer;
	void	reset_reload_timer() { m_reload_timer = MAX_RELOAD_TIME; }
private:
	bool		m_can_shoot;
	vector2f	m_position;
};
#endif // WEAPON_H
